#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "mbedtls/error.h"
#include "mbedtls/ssl.h"

#include "aem_file.h"
#include "defines.h"

#include "Includes/Brotli.h"

//#include "aef.h"
#include "http.h"
#include "https.h"
//#include "smtp.h"

// Allow restarting the server immediately after kill
static void allowQuickRestart(const int* sock) {
	const int optval = 1;
	setsockopt(*sock, SOL_SOCKET, SO_REUSEPORT, (const void*)&optval, sizeof(int));
}

static int initSocket(const int *sock, const int port) {
	struct sockaddr_in servAddr;
	bzero((char*)&servAddr, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(port);

	allowQuickRestart(sock);

	const int ret = bind(*sock, (struct sockaddr*)&servAddr, sizeof(servAddr));
	if (ret < 0) return ret;

	listen(*sock, 10); // socket, backlog (# of connections to keep in queue)
	return 0;
}

/*static int receiveConnections_aef() {
	int sock;
	if (initSocket(&sock, AEM_PORT_AEF) != 0) return 1;

	while(1) {
		const int sockNew = accept(sock, NULL, NULL);
		respond_aef(sockNew);
		close(sockNew);
	}

	return 0;
}*/

static int receiveConnections_http() {
	const int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (initSocket(&sock, AEM_PORT_HTTP) != 0) return 1;

	while(1) {
		const int sockNew = accept(sock, NULL, NULL);
		respond_http(sockNew);
		close(sockNew);
	}

	return 0;
}

static int aem_countFiles(const char *path, const char *ext, const size_t extLen) {
	DIR* dir = opendir(path);
	if (dir == NULL) return 0;

	int counter = 0;

	while(1) {
		struct dirent *de = readdir(dir);
		if (de == NULL) break;
		if (memcmp(de->d_name + strlen(de->d_name) - extLen, ext, extLen) == 0) counter++;
	}

	closedir(dir);
	return counter;
}

static void aem_loadFiles(const char *path, const char *ext, const size_t extLen, struct aem_file f[], const int fileCount) {
	DIR* dir = opendir(path);
	if (dir == NULL) return;

	for (int counter = 0; counter < fileCount;) {
		struct dirent *de = readdir(dir);
		if (de == NULL) {f[counter].lenData = 0; break;}

		if (memcmp(de->d_name + strlen(de->d_name) - extLen, ext, extLen) == 0) {
			char filePath[strlen(path) + strlen(de->d_name) + 1];
			sprintf(filePath, "%s/%s", path, de->d_name);

			int fd = open(filePath, O_RDONLY);
			if (fd < 0) {f[counter].lenData = 0; continue;}
			const off_t bytes = lseek(fd, 0, SEEK_END);
			f[counter].data = malloc(bytes);
			const ssize_t readBytes = pread(fd, f[counter].data,  bytes, 0);
			close(fd);

			if (readBytes == bytes) {
				f[counter].filename = strdup(de->d_name);
				f[counter].lenData = bytes;

				if (strcmp(ext, ".js") == 0 || strcmp(ext, ".css") == 0) {
					brotliCompress(&(f[counter].data), &(f[counter].lenData));
					printf("Loaded %s (%zd bytes compressed)\n", f[counter].filename, f[counter].lenData);
				} else {
					printf("Loaded %s (%zd bytes)\n", f[counter].filename, f[counter].lenData);
				}

			} else {
				printf("ERROR: Failed to load %s\n", de->d_name);
				free(f[counter].data);
			}

			counter++;
		}
	}

	closedir(dir);
}

static int receiveConnections_https(const int port) {
	// Load the certificate
	int fd = open("aem-https.crt", O_RDONLY);
	if (fd < 0) return 1;
	off_t lenFile = lseek(fd, 0, SEEK_END);

	unsigned char *cert = calloc(lenFile + 2, 1);
	ssize_t readBytes = pread(fd, cert, lenFile, 0);
	close(fd);
	if (readBytes != lenFile) {free(cert); return 2;}

	mbedtls_x509_crt srvcert;
	mbedtls_x509_crt_init(&srvcert);
	int ret = mbedtls_x509_crt_parse(&srvcert, cert, lenFile + 1);
	free(cert);

	if (ret != 0) {
		char error_buf[100];
		mbedtls_strerror(ret, error_buf, 100);
		printf("ERROR: Loading server cert failed - mbedtls_x509_crt_parse returned %d: %s\n", ret, error_buf);
		return 1;
	}

	// Load the private key
	fd = open("aem-https.key", O_RDONLY);
	if (fd < 0) return 1;
	lenFile = lseek(fd, 0, SEEK_END);

	unsigned char *key = calloc(lenFile + 2, 1);
	readBytes = pread(fd, key, lenFile, 0);
	close(fd);
	if (readBytes != lenFile) {free(key); return 1;}

	mbedtls_pk_context pkey;
	mbedtls_pk_init(&pkey);
	ret = mbedtls_pk_parse_key(&pkey, key, lenFile + 2, NULL, 0);
	free(key);
	if (ret != 0) {printf("ERROR: mbedtls_pk_parse_key returned %x\n", ret); return 1;}

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0) return 1;
	unsigned char seed[16];
	readBytes = read(fd, seed, 16);
	if (readBytes != 16) return 3;
	close(fd);

	int numCss = aem_countFiles("css", ".css",  4);
	int numImg = aem_countFiles("img", ".webp", 5);
	int numJs = aem_countFiles ("js",  ".js",   3);

	printf("Loading %d CSS files, %d images and %d Javascript files\n", numCss, numImg, numJs);

	struct aem_file fileCss[numCss + 1];
	struct aem_file fileImg[numImg + 1];
	struct aem_file fileJs[numJs + 1];

	if (numCss > 0) aem_loadFiles("css", ".css",  4, fileCss, numCss);
	if (numImg > 0) aem_loadFiles("img", ".webp", 5, fileImg, numImg);
	if (numJs  > 0) aem_loadFiles("js",  ".js",   3, fileJs,  numJs);

	struct aem_fileSet fileSet;
	fileSet.cssFiles = fileCss;
	fileSet.imgFiles = fileImg;
	fileSet.jsFiles  = fileJs;
	fileSet.cssCount = numCss;
	fileSet.imgCount = numImg;
	fileSet.jsCount  = numJs;

	const int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {puts("ERROR: Opening socket failed"); return 2;}
	if (initSocket(&sock, port) != 0) {puts("ERROR: Binding socket failed"); return 3;}

	while(1) {
		struct sockaddr_in clientAddr;
		unsigned int clen = sizeof(clientAddr);
		const int newSock = accept(sock, (struct sockaddr*)&clientAddr, &clen);
		if (newSock < 0) {puts("ERROR: Failed to create socket for accepting connection"); break;}

		const int pid = fork();
		if (pid < 0) {puts("ERROR: Failed fork"); break;}
		else if (pid == 0) {
			// Child goes on to communicate with the client
			respond_https(newSock, &srvcert, &pkey, clientAddr.sin_addr.s_addr, seed, &fileSet);
			break;
		} else close(newSock); // Parent closes its copy of the socket and moves on to accept a new one
	}

	for (int i = 0; i < numCss; i++) {free(fileCss[i].filename); free(fileCss[i].data);}
	for (int i = 0; i < numImg; i++) {free(fileImg[i].filename); free(fileImg[i].data);}
	for (int i = 0; i < numJs;  i++) {free(fileJs[i].filename);  free(fileJs[i].data);}

	mbedtls_x509_crt_free(&srvcert);
	mbedtls_pk_free(&pkey);
	close(sock);
	return 0;
}

/*static int receiveConnections_smtp() {
	int sock;
	if (initSocket(&sock, AEM_PORT_SMTP) != 0) return 1;

	while(1) {
		const int sockNew = accept(sock, NULL, NULL);
		respond_smtp(sockNew);
		close(sockNew);
	}

	return 0;
}*/

int main() {
	if (signal(SIGCHLD, SIG_IGN) == SIG_ERR) {puts("ERROR: signal failed"); return 4;} // Prevent zombie processes
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {puts("ERROR: signal failed"); return 4;} // Prevent writing to closed/invalid sockets from ending the process

	puts(">>> ae-mail: All-Ears Mail");

	int pid;

	pid = fork();
	if (pid < 0) return 1;
	if (pid == 0) return 0; //receiveConnections(AEM_PORT_AEF);

	pid = fork();
	if (pid < 0) return 1;
	if (pid == 0) return receiveConnections_https(AEM_PORT_HTTPS);

	pid = fork();
	if (pid < 0) return 1;
//	if (pid == 0) return receiveConnections(AEM_PORT_SMTP);

	receiveConnections_http(AEM_PORT_HTTP);

	return 0;
}
