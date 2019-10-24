#include <stdlib.h>
#include <string.h>

__attribute__((warn_unused_result))
static unsigned char hexToChar(const char * const src) {
	char hex[3];
	memcpy(hex, src, 2);
	hex[2] = '\0';
	return strtol(hex, NULL, 16);
}

void decodeQuotedPrintable(char * const data, size_t * const lenData) {
	while(1) {
		char * const enc = memchr(data, '=', *lenData - 1);
		if (enc == NULL) break;

		const int x = (data + *lenData) - (enc + 3);
		if (x < 0) break;

		*enc = hexToChar(enc + 1);
		if (*enc == '=') *enc = '\x01';

		memmove(enc + 1, enc + 3, x);
		*lenData -= 2;
	}

	while(1) {
		char * const equalsign = memchr(data, '\x01', *lenData);
		if (equalsign == NULL) break;
		*equalsign = '=';
	}
}