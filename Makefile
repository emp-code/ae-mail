CC=gcc
CFLAGS=-O2 -march=native -pipe -Wall -Wextra -Wno-comment -D_GNU_SOURCE -D_FORTIFY_SOURCE=2 -fstack-protector-strong -fcf-protection=full -fPIE -pie -Wl,-z,relro,-z,now -Wl,-z,noexecstack -Werror=incompatible-pointer-types -Werror=implicit-function-declaration

all: aem-manager aem-account aem-enquiry aem-storage aem-mta aem-web-clr aem-web-oni aem-api-clr aem-api-oni utils/Accgen utils/BinCrypt utils/Keygen utils/ManagerClient Data/gen_address Data/gen_dkim Data/gen_internal Data/gen_html Data/gen_tls

aem-manager: manager/*.c
	$(CC) $(CFLAGS) -DAEM_MANAGER -o aem-manager manager/*.c Common/CreateSocket.c Common/ToggleEcho.c Common/ValidFd.c -lsodium -lcap

aem-account: account/*.c
	$(CC) $(CFLAGS) -DAEM_ACCOUNT -o aem-account account/*.c Common/SetCaps.c Common/UnixSocketClient.c -lsodium -lcap -lm

aem-enquiry: enquiry/*.c
	$(CC) $(CFLAGS) -DAEM_ENQUIRY -o aem-enquiry enquiry/*.c Common/SetCaps.c Common/ValidDomain.c Common/ValidIp.c -lsodium -lcap -lmbedtls -lmbedcrypto -lmbedx509 -lmaxminddb

aem-storage: storage/*.c
	$(CC) $(CFLAGS) -DAEM_STORAGE -o aem-storage storage/*.c Common/SetCaps.c Common/aes.c -lsodium -lcap

aem-web-clr: web-clr/*.c
	$(CC) $(CFLAGS) -DAEM_WEB -DAEM_WEB_CLR -o aem-web-clr web-clr/*.c Common/tls_common.c Common/CreateSocket.c Common/SetCaps.c -lsodium -lcap -lmbedtls -lmbedcrypto -lmbedx509

aem-web-oni: web-oni/main.c
	$(CC) $(CFLAGS) -DAEM_WEB -DAEM_WEB_ONI -DAEM_IS_ONION -o aem-web-oni web-oni/main.c Common/SetCaps.c Common/CreateSocket.c -lsodium -lcap

aem-api-clr: api-clr/*.c
	$(CC) $(CFLAGS) -DAEM_API_CLR -DAEM_API -o aem-api-clr api-clr/*.c api-common/*.c Common/Addr32.c Common/CreateSocket.c Common/SetCaps.c Common/UnixSocketClient.c Common/ValidDomain.c Common/ValidEmail.c Common/ValidUtf8.c Common/aes.c Common/tls_common.c -lsodium -lcap -lmbedtls -lmbedcrypto -lmbedx509

aem-api-oni: api-oni/*.c
	$(CC) $(CFLAGS) -DAEM_API_ONI -DAEM_API -DAEM_IS_ONION -o aem-api-oni api-oni/*.c api-common/*.c Common/Addr32.c Common/CreateSocket.c Common/SetCaps.c Common/UnixSocketClient.c Common/ValidDomain.c Common/ValidEmail.c Common/ValidUtf8.c Common/aes.c -lsodium -lcap -lmbedtls -lmbedcrypto -lmbedx509

aem-mta: mta/*.c
	$(CC) $(CFLAGS) -DAEM_MTA -o aem-mta mta/*.c Common/SetCaps.c Common/Addr32.c Common/CreateSocket.c Common/HtmlToText.c Common/HtmlRefs.c Common/ref2codepoint.c Common/QuotedPrintable.c Common/UnixSocketClient.c Common/ToUtf8.c Common/Trim.c Common/ValidIp.c -lsodium -lcap -lmbedtls -lmbedcrypto -lmbedx509 -lbrotlienc -licuuc -licui18n

utils/Accgen: utils/Accgen.c
	$(CC) $(CFLAGS) -o utils/Accgen utils/Accgen.c utils/GetKey.c Common/ToggleEcho.c -lsodium

utils/BinCrypt: utils/BinCrypt.c
	$(CC) $(CFLAGS) -o utils/BinCrypt utils/BinCrypt.c utils/GetKey.c Common/ToggleEcho.c -lsodium

utils/Keygen: utils/Keygen.c
	$(CC) $(CFLAGS) -o utils/Keygen utils/Keygen.c -lsodium

utils/ManagerClient: utils/ManagerClient.c
	$(CC) $(CFLAGS) -o utils/ManagerClient utils/ManagerClient.c utils/GetKey.c Common/ToggleEcho.c -lsodium

Data/gen_address: Data/gen_address.c
	$(CC) $(CFLAGS) -o Data/gen_address Data/gen_address.c -lsodium

Data/gen_html: Data/gen_html.c
	$(CC) $(CFLAGS) -o Data/gen_html Data/gen_html.c utils/GetKey.c Common/ToggleEcho.c -lsodium -lbrotlienc -lzopfli

Data/gen_internal: Data/gen_internal.c
	$(CC) $(CFLAGS) -o Data/gen_internal Data/gen_internal.c -lsodium

Data/gen_dkim: Data/gen_dkim.c
	$(CC) $(CFLAGS) -o Data/gen_dkim Data/gen_dkim.c

Data/gen_tls: Data/gen_tls.c
	$(CC) $(CFLAGS) -o Data/gen_tls Data/gen_tls.c

.PHONY: clean
clean:
	-rm aem-manager aem-account aem-enquiry aem-storage aem-mta aem-web-clr aem-web-oni aem-api-clr aem-api-oni utils/Accgen utils/BinCrypt utils/Keygen utils/ManagerClient Data/gen_address Data/gen_dkim Data/gen_internal Data/gen_html Data/gen_tls
