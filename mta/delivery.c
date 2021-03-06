#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>

#include <brotli/encode.h>
#include <sodium.h>

#include "../Common/Addr32.h"
#include "../Common/UnixSocketClient.h"

#include "delivery.h"

#include "../Global.h"

static unsigned char sign_skey[crypto_sign_SECRETKEYBYTES];

void setSignKey(const unsigned char * const seed) {
	unsigned char tmp[crypto_sign_PUBLICKEYBYTES];
	crypto_sign_seed_keypair(tmp, sign_skey, seed);
}

void delSignKey(void) {
	sodium_memzero(sign_skey, crypto_sign_SECRETKEYBYTES);
}

#include "../Common/Message.c"

__attribute__((warn_unused_result))
static unsigned char *makeExtMsg(struct emailInfo * const email, const unsigned char * const upk, size_t * const lenOut, const bool allVer) {
	if (!allVer && email->body != NULL && email->lenBody > 0) { // Remove non-preferred variant(s) if requested
		const unsigned char * const r = memrchr(email->body, AEM_CET_CHAR_SEP, email->lenBody);
		if (r != NULL) {
			const size_t lenRem = (r + 1 - email->body);
			memmove(email->body, r + 1, email->lenBody - lenRem);
			email->lenBody -= lenRem;
		}
	}

	if (email->lenEnvTo > 31) email->lenEnvTo = 31;
	if (email->lenHdrTo > 63) email->lenHdrTo = 63;
	if (email->lenGreet > 63) email->lenGreet = 63;
	if (email->lenRvDns > 63) email->lenRvDns = 63;
	if (email->lenAuSys > 63) email->lenAuSys = 63;

	size_t lenUncomp =
		email->lenEnvTo +
		email->lenHdrTo +
		email->lenGreet +
		email->lenRvDns +
		email->lenAuSys +
		email->lenEnvFr +
		email->lenHdrFr +
		email->lenHdrRt +
		email->lenMsgId +
		email->lenSbjct +
		email->lenBody +
		((email->lenBody > 0) ? 6 : 5) +
		(email->lenHead > 1 ? (email->lenHead - 1) : 0);

	if (email->dkimCount > 7) email->dkimCount = 7;
	if (email->dkimCount > 6) lenUncomp += email->dkim[6].lenDomain;
	if (email->dkimCount > 5) lenUncomp += email->dkim[5].lenDomain;
	if (email->dkimCount > 4) lenUncomp += email->dkim[4].lenDomain;
	if (email->dkimCount > 3) lenUncomp += email->dkim[3].lenDomain;
	if (email->dkimCount > 2) lenUncomp += email->dkim[2].lenDomain;
	if (email->dkimCount > 1) lenUncomp += email->dkim[1].lenDomain;
	if (email->dkimCount > 0) lenUncomp += email->dkim[0].lenDomain;

	unsigned char * const uncomp = malloc(lenUncomp);
	if (uncomp == NULL) return NULL;

	size_t offset = 0;

	// DKIM domains
	for (int i = 0; i < email->dkimCount; i++) {
		memcpy(uncomp + offset, email->dkim[i].domain, email->dkim[i].lenDomain);
		offset += email->dkim[i].lenDomain;
	}

	// The five short-text fields
	memcpy(uncomp + offset, email->envTo, email->lenEnvTo); offset += email->lenEnvTo;
	memcpy(uncomp + offset, email->hdrTo, email->lenHdrTo); offset += email->lenHdrTo;
	memcpy(uncomp + offset, email->greet, email->lenGreet); offset += email->lenGreet;
	memcpy(uncomp + offset, email->rvDns, email->lenRvDns); offset += email->lenRvDns;
	memcpy(uncomp + offset, email->auSys, email->lenAuSys); offset += email->lenAuSys;

	// The five long-text fields
	memcpy(uncomp + offset, email->envFr, email->lenEnvFr); offset += email->lenEnvFr; uncomp[offset] = '\n'; offset++;
	memcpy(uncomp + offset, email->hdrFr, email->lenHdrFr); offset += email->lenHdrFr; uncomp[offset] = '\n'; offset++;
	memcpy(uncomp + offset, email->hdrRt, email->lenHdrRt); offset += email->lenHdrRt; uncomp[offset] = '\n'; offset++;
	memcpy(uncomp + offset, email->msgId, email->lenMsgId); offset += email->lenMsgId; uncomp[offset] = '\n'; offset++;
	memcpy(uncomp + offset, email->sbjct, email->lenSbjct); offset += email->lenSbjct; uncomp[offset] = '\n'; offset++;

	// The headers and body
	if (email->lenHead > 1) {
		memcpy(uncomp + offset, email->head + 1, email->lenHead - 1); // Ignore leading linebreak
		offset += email->lenHead - 1;
	}

	if (email->lenBody > 0) {
		uncomp[offset] = AEM_CET_CHAR_SEP;
		offset++;
		memcpy(uncomp + offset, email->body, email->lenBody);
	}

	// Compress the data
	size_t lenComp = lenUncomp + 256; // +256 in case compressed is larger
	unsigned char * const comp = malloc(lenComp);
	if (comp == NULL) {
		free(uncomp);
		return NULL;
	}

	if (BrotliEncoderCompress(BROTLI_MAX_QUALITY, BROTLI_MAX_WINDOW_BITS, BROTLI_DEFAULT_MODE, lenUncomp, uncomp, &lenComp, comp) == BROTLI_FALSE) {
		free(uncomp);
		free(comp);
		return NULL;
	}

	free(uncomp);

	// Create the ExtMsg
	const size_t lenContent = 23 + (email->dkimCount * 3) + lenComp;
	if (lenContent + crypto_sign_BYTES + crypto_box_SEALBYTES > 1048752) { // ((2^16 - 1) + 12) * 16
		free(comp);
		return NULL;
	}

	unsigned char * const content = calloc(lenContent, 1);
	if (content == NULL) {
		free(comp);
		return NULL;
	}

	// Universal Part
	content[0] = msg_getPadAmount(lenContent);
	memcpy(content + 1, &(email->timestamp), 4);

	// ExtMsg Part
	memcpy(content + 5, &email->ip, 4);
	memcpy(content + 9, &email->tls_ciphersuite, 2);
	content[11] = email->tlsInfo;

	// The 9 InfoBytes
	content[12] = (email->dkimCount << 5) | (email->attachCount & 31);

	content[13] = email->ccBytes[0];
	if (email->ipBlacklisted)   content[13] |= 128;
	if (email->ipMatchGreeting) content[13] |=  64;
	if (email->protocolEsmtp)   content[13] |=  32;

	content[14] = email->ccBytes[1];
	if (email->invalidCommands)   content[14] |= 128;
	if (email->protocolViolation) content[14] |=  63;
	if (email->rareCommands)      content[14] |=  32;

	content[15] = (email->spf   & 192) /*| (email-> ? 32 : 0)*/ | (email->lenEnvTo & 31);
	content[16] = (email->dmarc & 192) | (email->lenHdrTo & 63);

	content[17] = email->lenGreet & 63;
	if (email->dnssec) content[17] |= 128;

	content[18] = email->lenRvDns & 63;
	if (email->dane) content[18] |= 128;

	content[19] = email->lenAuSys & 63;
	// [19] & 192 unused

	content[20] = email->hdrTz & 127;
	if (email->dkimFailed) content[20] |= 128;

	memcpy(content + 21, &email->hdrTs, 2);

	// DKIM
	offset = 23;
	for (int i = 0; i < email->dkimCount; i++) {
		if (email->dkim[i].algoRsa)    content[offset] |= 128;
		if (email->dkim[i].algoSha256) content[offset] |=  64;
		if (email->dkim[i].dnsFlag_s)  content[offset] |=  32;
		if (email->dkim[i].dnsFlag_y)  content[offset] |=  16;
		if (email->dkim[i].headSimple) content[offset] |=   8;
		if (email->dkim[i].bodySimple) content[offset] |=   4;

		const int64_t expiry = email->dkim[i].ts_expr - email->timestamp;
		// 0: Expired
		if (email->dkim[i].ts_expr == 0) content[offset] |= 1; // 1: Expiration disabled or value invalid
		else if (expiry >= 2629746)      content[offset] |= 2; // 2: Long expiration: >= 1 month
		else if (expiry >  0)            content[offset] |= 3; // 3: Short expiration: < 1 month

		if (email->dkim[i].fullId)     content[offset + 1] |= 128;
		if (email->dkim[i].sgnAll)     content[offset + 1] |=  64;
		if (email->dkim[i].sgnDate)    content[offset + 1] |=  32;
		if (email->dkim[i].sgnFrom)    content[offset + 1] |=  16;
		if (email->dkim[i].sgnMsgId)   content[offset + 1] |=   8;
		if (email->dkim[i].sgnReplyTo) content[offset + 1] |=   4;
		if (email->dkim[i].sgnSubject) content[offset + 1] |=   2;
		if (email->dkim[i].sgnTo)      content[offset + 1] |=   1;

		if (email->dkim[i].bodyTrunc)  content[offset + 2] |= 128;
		if ((int64_t)email->timestamp - email->dkim[i].ts_sign > 30) content[offset + 2] |= 64;
		content[offset + 2] |= (email->dkim[i].lenDomain - 4) & 63;

		offset += 3;
	}

	// The compressed body
	memcpy(content + offset, comp, lenComp);
	free(comp);

	// Encrypt into the final form
	unsigned char throwaway[crypto_box_PUBLICKEYBYTES];
	randombytes_buf(throwaway, crypto_box_PUBLICKEYBYTES);

	unsigned char zero[crypto_box_PUBLICKEYBYTES];
	bzero(zero, crypto_box_PUBLICKEYBYTES);

	unsigned char * const encrypted = msg_encrypt((memcmp(zero, upk, crypto_box_PUBLICKEYBYTES) == 0) ? throwaway : upk, content, lenContent, lenOut);
	free(content);
	if (encrypted == NULL) syslog(LOG_ERR, "Failed creating encrypted message");

	return encrypted;
}

static int sendMsg(const int sock, unsigned char * const msg, const size_t lenMsg) {
	if (sock < 0 || msg == NULL || lenMsg < AEM_MSG_MINSIZE || lenMsg % 16 != 0) {syslog(LOG_ERR, "sendMsg: Invalid data"); return AEM_STORE_INERROR;}

	char ret = AEM_STORE_INERROR;
	const bool sockOk = (send(sock, msg, lenMsg, 0) == (ssize_t)lenMsg && recv(sock, &ret, 1, 0) == 1);
	free(msg);

	if (sockOk) {
		if (ret == 0) return 0;
		send(sock, (unsigned char[]){0xFE}, 1, 0);
	} else syslog(LOG_ERR, "Failed sending to Storage");

	close(sock);
	return ret;
}

int deliverMessage(char to[AEM_SMTP_MAX_TO][32], const unsigned char toUpk[AEM_SMTP_MAX_TO][crypto_box_PUBLICKEYBYTES], const uint8_t toFlags[AEM_SMTP_MAX_TO], const int toCount, struct emailInfo * const email, const unsigned char * const original, const size_t lenOriginal, const bool brOriginal) {
	if (to == NULL || toCount < 1 || email == NULL) {syslog(LOG_ERR, "deliverMessage(): Empty"); return AEM_STORE_INERROR;}
	if (email->attachCount > 31) email->attachCount = 31;

	// Deliver
	for (int i = 0; i < toCount; i++) {
		email->lenEnvTo = strlen(to[i]);
		if (email->lenEnvTo > 31) email->lenEnvTo = 31;
		memcpy(email->envTo, to[i], email->lenEnvTo);

		size_t lenEnc = 0;
		unsigned char *enc = makeExtMsg(email, toUpk[i], &lenEnc, (toFlags[i] & AEM_ADDR_FLAG_ALLVER) != 0);
		if (enc == NULL || lenEnc < 1 || lenEnc % 16 != 0) {
			syslog(LOG_ERR, "makeExtMsg failed (%zu)", lenEnc);
			continue;
		}

		unsigned char msgId[16];
		memcpy(msgId, enc, 16);

		// Deliver
		const int stoSock = storageSocket(AEM_MTA_INSERT, toUpk[i], crypto_box_PUBLICKEYBYTES);
		if (stoSock < 0) {free(enc); continue;}

		int ret = sendMsg(stoSock, enc, lenEnc);
		if (ret != 0) {if (toCount > 1) continue; return ret;}

		// Store attachments, if requested
		if ((toFlags[i] & AEM_ADDR_FLAG_ATTACH) != 0) {
			for (int j = 0; j < email->attachCount; j++) {
				if (email->attachment[j] == NULL) {syslog(LOG_ERR, "Attachment null"); break;}

				unsigned char * const att = malloc(5 + email->lenAttachment[j]);
				if (att == NULL) {syslog(LOG_ERR, "Failed allocation"); break;}

				att[0] = msg_getPadAmount(5 + email->lenAttachment[j]) | 32;
				memcpy(att + 1, &(email->timestamp), 4);
				memcpy(att + 5, email->attachment[j], email->lenAttachment[j]);
				memcpy(att + 6, msgId, 16);

				enc = msg_encrypt(toUpk[i], att, 5 + email->lenAttachment[j], &lenEnc);
				free(att);

				ret = sendMsg(stoSock, enc, lenEnc);
				if (ret != 0) {if (toCount > 1) continue; return ret;}
			}
		}

		// Store original, if requested
		if (original != NULL && lenOriginal > 0 && (toFlags[i] & AEM_ADDR_FLAG_ORIGIN) != 0) {
			const char * const fn = brOriginal? "src.eml.br" : "src.eml";
			const size_t lenFn = brOriginal? 10 : 7;

			const size_t lenAtt = 22 + lenFn + lenOriginal;
			unsigned char * const att = malloc(lenAtt);
			if (att != NULL) {
				att[0] = msg_getPadAmount(lenAtt) | 32;
				memcpy(att + 1, &(email->timestamp), 4);
				att[5] = lenFn - 1;
				memcpy(att + 6, msgId, 16);
				memcpy(att + 22, fn, lenFn);
				memcpy(att + 22 + lenFn, original, lenOriginal);
			} else syslog(LOG_ERR, "Failed allocation");

			enc = msg_encrypt(toUpk[i], att, lenAtt, &lenEnc);
			free(att);

			ret = sendMsg(stoSock, enc, lenEnc);
			if (ret != 0) {if (toCount > 1) continue; return ret;}
		}

		// Final End
		send(stoSock, (unsigned char[]){0xFE}, 1, 0);
		close(stoSock);
	}

	return 0;
}
