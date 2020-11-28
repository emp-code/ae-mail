#define AEM_TLS_CIPHERSUITES_HIGH \
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_CHACHA20_POLY1305_SHA256,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_CHACHA20_POLY1305_SHA256,\
	0

#define AEM_TLS_CIPHERSUITES_OUT \
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384,\
	MBEDTLS_TLS_DHE_RSA_WITH_AES_256_GCM_SHA384,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_CHACHA20_POLY1305_SHA256,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_CHACHA20_POLY1305_SHA256,\
	MBEDTLS_TLS_DHE_RSA_WITH_CHACHA20_POLY1305_SHA256,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_256_CCM,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_256_CCM_8,\
	MBEDTLS_TLS_DHE_RSA_WITH_AES_256_CCM,\
	MBEDTLS_TLS_DHE_RSA_WITH_AES_256_CCM_8,\
	MBEDTLS_TLS_DHE_RSA_WITH_CAMELLIA_256_GCM_SHA384,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_CAMELLIA_256_GCM_SHA384,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_CAMELLIA_256_GCM_SHA384,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256,\
	MBEDTLS_TLS_DHE_RSA_WITH_AES_128_GCM_SHA256,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_128_CCM,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_128_CCM_8,\
	MBEDTLS_TLS_DHE_RSA_WITH_AES_128_CCM,\
	MBEDTLS_TLS_DHE_RSA_WITH_AES_128_CCM_8,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_CAMELLIA_128_GCM_SHA256,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_CAMELLIA_128_GCM_SHA256,\
	MBEDTLS_TLS_DHE_RSA_WITH_CAMELLIA_128_GCM_SHA256,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_ARIA_256_GCM_SHA384,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_ARIA_256_GCM_SHA384,\
	MBEDTLS_TLS_DHE_RSA_WITH_ARIA_256_GCM_SHA384,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_ARIA_128_GCM_SHA256,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_ARIA_128_GCM_SHA256,\
	MBEDTLS_TLS_DHE_RSA_WITH_ARIA_128_GCM_SHA256,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384,\
	MBEDTLS_TLS_DHE_RSA_WITH_AES_256_CBC_SHA256,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_CAMELLIA_256_CBC_SHA384,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_CAMELLIA_256_CBC_SHA384,\
	MBEDTLS_TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA256,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256,\
	MBEDTLS_TLS_DHE_RSA_WITH_AES_128_CBC_SHA256,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_CAMELLIA_128_CBC_SHA256,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_CAMELLIA_128_CBC_SHA256,\
	MBEDTLS_TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA256,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_ARIA_256_CBC_SHA384,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_ARIA_256_CBC_SHA384,\
	MBEDTLS_TLS_DHE_RSA_WITH_ARIA_256_CBC_SHA384,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_ARIA_128_CBC_SHA256,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_ARIA_128_CBC_SHA256,\
	MBEDTLS_TLS_DHE_RSA_WITH_ARIA_128_CBC_SHA256,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_AES_256_GCM_SHA384,\
	MBEDTLS_TLS_ECDH_RSA_WITH_AES_256_GCM_SHA384,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_CAMELLIA_256_GCM_SHA384,\
	MBEDTLS_TLS_ECDH_RSA_WITH_CAMELLIA_256_GCM_SHA384,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256,\
	MBEDTLS_TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_CAMELLIA_128_GCM_SHA256,\
	MBEDTLS_TLS_ECDH_RSA_WITH_CAMELLIA_128_GCM_SHA256,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_ARIA_256_GCM_SHA384,\
	MBEDTLS_TLS_ECDH_RSA_WITH_ARIA_256_GCM_SHA384,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_ARIA_128_GCM_SHA256,\
	MBEDTLS_TLS_ECDH_RSA_WITH_ARIA_128_GCM_SHA256,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA384,\
	MBEDTLS_TLS_ECDH_RSA_WITH_AES_256_CBC_SHA384,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_CAMELLIA_256_CBC_SHA384,\
	MBEDTLS_TLS_ECDH_RSA_WITH_CAMELLIA_256_CBC_SHA384,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256,\
	MBEDTLS_TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_CAMELLIA_128_CBC_SHA256,\
	MBEDTLS_TLS_ECDH_RSA_WITH_CAMELLIA_128_CBC_SHA256,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_ARIA_256_CBC_SHA384,\
	MBEDTLS_TLS_ECDH_RSA_WITH_ARIA_256_CBC_SHA384,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_ARIA_128_CBC_SHA256,\
	MBEDTLS_TLS_ECDH_RSA_WITH_ARIA_128_CBC_SHA256,\
	MBEDTLS_TLS_RSA_WITH_AES_256_GCM_SHA384,\
	MBEDTLS_TLS_RSA_WITH_AES_256_CCM,\
	MBEDTLS_TLS_RSA_WITH_AES_256_CCM_8,\
	MBEDTLS_TLS_RSA_WITH_CAMELLIA_256_GCM_SHA384,\
	MBEDTLS_TLS_RSA_WITH_AES_128_GCM_SHA256,\
	MBEDTLS_TLS_RSA_WITH_AES_128_CCM,\
	MBEDTLS_TLS_RSA_WITH_AES_128_CCM_8,\
	MBEDTLS_TLS_RSA_WITH_CAMELLIA_128_GCM_SHA256,\
	MBEDTLS_TLS_RSA_WITH_ARIA_256_GCM_SHA384,\
	MBEDTLS_TLS_RSA_WITH_ARIA_128_GCM_SHA256,\
	MBEDTLS_TLS_RSA_WITH_AES_256_CBC_SHA256,\
	MBEDTLS_TLS_RSA_WITH_CAMELLIA_256_CBC_SHA256,\
	MBEDTLS_TLS_RSA_WITH_AES_128_CBC_SHA256,\
	MBEDTLS_TLS_RSA_WITH_CAMELLIA_128_CBC_SHA256,\
	MBEDTLS_TLS_RSA_WITH_ARIA_256_CBC_SHA384,\
	MBEDTLS_TLS_RSA_WITH_ARIA_128_CBC_SHA256,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA,\
	MBEDTLS_TLS_DHE_RSA_WITH_AES_256_CBC_SHA,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA,\
	MBEDTLS_TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA,\
	MBEDTLS_TLS_DHE_RSA_WITH_AES_128_CBC_SHA,\
	MBEDTLS_TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA,\
	MBEDTLS_TLS_ECDH_RSA_WITH_AES_256_CBC_SHA,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA,\
	MBEDTLS_TLS_ECDH_RSA_WITH_AES_128_CBC_SHA,\
	MBEDTLS_TLS_RSA_WITH_AES_256_CBC_SHA,\
	MBEDTLS_TLS_RSA_WITH_CAMELLIA_256_CBC_SHA,\
	MBEDTLS_TLS_RSA_WITH_AES_128_CBC_SHA,\
	MBEDTLS_TLS_RSA_WITH_CAMELLIA_128_CBC_SHA,\
	0

#define AEM_TLS_CIPHERSUITES_MTA \
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384,\
	MBEDTLS_TLS_DHE_RSA_WITH_AES_256_GCM_SHA384,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_CHACHA20_POLY1305_SHA256,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_CHACHA20_POLY1305_SHA256,\
	MBEDTLS_TLS_DHE_RSA_WITH_CHACHA20_POLY1305_SHA256,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_256_CCM,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_256_CCM_8,\
	MBEDTLS_TLS_DHE_RSA_WITH_AES_256_CCM,\
	MBEDTLS_TLS_DHE_RSA_WITH_AES_256_CCM_8,\
	MBEDTLS_TLS_DHE_RSA_WITH_CAMELLIA_256_GCM_SHA384,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_CAMELLIA_256_GCM_SHA384,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_CAMELLIA_256_GCM_SHA384,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256,\
	MBEDTLS_TLS_DHE_RSA_WITH_AES_128_GCM_SHA256,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_128_CCM,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_128_CCM_8,\
	MBEDTLS_TLS_DHE_RSA_WITH_AES_128_CCM,\
	MBEDTLS_TLS_DHE_RSA_WITH_AES_128_CCM_8,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_CAMELLIA_128_GCM_SHA256,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_CAMELLIA_128_GCM_SHA256,\
	MBEDTLS_TLS_DHE_RSA_WITH_CAMELLIA_128_GCM_SHA256,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_ARIA_256_GCM_SHA384,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_ARIA_256_GCM_SHA384,\
	MBEDTLS_TLS_DHE_RSA_WITH_ARIA_256_GCM_SHA384,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_ARIA_128_GCM_SHA256,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_ARIA_128_GCM_SHA256,\
	MBEDTLS_TLS_DHE_RSA_WITH_ARIA_128_GCM_SHA256,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384,\
	MBEDTLS_TLS_DHE_RSA_WITH_AES_256_CBC_SHA256,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_CAMELLIA_256_CBC_SHA384,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_CAMELLIA_256_CBC_SHA384,\
	MBEDTLS_TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA256,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256,\
	MBEDTLS_TLS_DHE_RSA_WITH_AES_128_CBC_SHA256,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_CAMELLIA_128_CBC_SHA256,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_CAMELLIA_128_CBC_SHA256,\
	MBEDTLS_TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA256,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_ARIA_256_CBC_SHA384,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_ARIA_256_CBC_SHA384,\
	MBEDTLS_TLS_DHE_RSA_WITH_ARIA_256_CBC_SHA384,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_ARIA_128_CBC_SHA256,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_ARIA_128_CBC_SHA256,\
	MBEDTLS_TLS_DHE_RSA_WITH_ARIA_128_CBC_SHA256,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_AES_256_GCM_SHA384,\
	MBEDTLS_TLS_ECDH_RSA_WITH_AES_256_GCM_SHA384,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_CAMELLIA_256_GCM_SHA384,\
	MBEDTLS_TLS_ECDH_RSA_WITH_CAMELLIA_256_GCM_SHA384,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256,\
	MBEDTLS_TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_CAMELLIA_128_GCM_SHA256,\
	MBEDTLS_TLS_ECDH_RSA_WITH_CAMELLIA_128_GCM_SHA256,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_ARIA_256_GCM_SHA384,\
	MBEDTLS_TLS_ECDH_RSA_WITH_ARIA_256_GCM_SHA384,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_ARIA_128_GCM_SHA256,\
	MBEDTLS_TLS_ECDH_RSA_WITH_ARIA_128_GCM_SHA256,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA384,\
	MBEDTLS_TLS_ECDH_RSA_WITH_AES_256_CBC_SHA384,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_CAMELLIA_256_CBC_SHA384,\
	MBEDTLS_TLS_ECDH_RSA_WITH_CAMELLIA_256_CBC_SHA384,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256,\
	MBEDTLS_TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_CAMELLIA_128_CBC_SHA256,\
	MBEDTLS_TLS_ECDH_RSA_WITH_CAMELLIA_128_CBC_SHA256,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_ARIA_256_CBC_SHA384,\
	MBEDTLS_TLS_ECDH_RSA_WITH_ARIA_256_CBC_SHA384,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_ARIA_128_CBC_SHA256,\
	MBEDTLS_TLS_ECDH_RSA_WITH_ARIA_128_CBC_SHA256,\
	MBEDTLS_TLS_RSA_WITH_AES_256_GCM_SHA384,\
	MBEDTLS_TLS_RSA_WITH_AES_256_CCM,\
	MBEDTLS_TLS_RSA_WITH_AES_256_CCM_8,\
	MBEDTLS_TLS_RSA_WITH_CAMELLIA_256_GCM_SHA384,\
	MBEDTLS_TLS_RSA_WITH_AES_128_GCM_SHA256,\
	MBEDTLS_TLS_RSA_WITH_AES_128_CCM,\
	MBEDTLS_TLS_RSA_WITH_AES_128_CCM_8,\
	MBEDTLS_TLS_RSA_WITH_CAMELLIA_128_GCM_SHA256,\
	MBEDTLS_TLS_RSA_WITH_ARIA_256_GCM_SHA384,\
	MBEDTLS_TLS_RSA_WITH_ARIA_128_GCM_SHA256,\
	MBEDTLS_TLS_RSA_WITH_AES_256_CBC_SHA256,\
	MBEDTLS_TLS_RSA_WITH_CAMELLIA_256_CBC_SHA256,\
	MBEDTLS_TLS_RSA_WITH_AES_128_CBC_SHA256,\
	MBEDTLS_TLS_RSA_WITH_CAMELLIA_128_CBC_SHA256,\
	MBEDTLS_TLS_RSA_WITH_ARIA_256_CBC_SHA384,\
	MBEDTLS_TLS_RSA_WITH_ARIA_128_CBC_SHA256,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA,\
	MBEDTLS_TLS_DHE_RSA_WITH_AES_256_CBC_SHA,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA,\
	MBEDTLS_TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA,\
	MBEDTLS_TLS_DHE_RSA_WITH_AES_128_CBC_SHA,\
	MBEDTLS_TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA,\
	MBEDTLS_TLS_ECDH_RSA_WITH_AES_256_CBC_SHA,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA,\
	MBEDTLS_TLS_ECDH_RSA_WITH_AES_128_CBC_SHA,\
	MBEDTLS_TLS_RSA_WITH_AES_256_CBC_SHA,\
	MBEDTLS_TLS_RSA_WITH_CAMELLIA_256_CBC_SHA,\
	MBEDTLS_TLS_RSA_WITH_AES_128_CBC_SHA,\
	MBEDTLS_TLS_RSA_WITH_CAMELLIA_128_CBC_SHA,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_RC4_128_SHA,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_RC4_128_SHA,\
	MBEDTLS_TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA,\
	MBEDTLS_TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA,\
	MBEDTLS_TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_RC4_128_SHA,\
	MBEDTLS_TLS_ECDH_RSA_WITH_RC4_128_SHA,\
	MBEDTLS_TLS_ECDH_ECDSA_WITH_3DES_EDE_CBC_SHA,\
	MBEDTLS_TLS_ECDH_RSA_WITH_3DES_EDE_CBC_SHA,\
	MBEDTLS_TLS_RSA_WITH_3DES_EDE_CBC_SHA,\
	MBEDTLS_TLS_RSA_WITH_RC4_128_SHA,\
	MBEDTLS_TLS_RSA_WITH_RC4_128_MD5,\
	0

#define AEM_TLS_CURVES_HIGH \
	MBEDTLS_ECP_DP_SECP384R1,\
	MBEDTLS_ECP_DP_SECP521R1,\
	MBEDTLS_ECP_DP_NONE

#define AEM_TLS_CURVES_OUT \
	MBEDTLS_ECP_DP_SECP384R1,\
	MBEDTLS_ECP_DP_SECP521R1,\
	MBEDTLS_ECP_DP_SECP256R1,\
	MBEDTLS_ECP_DP_NONE

#define AEM_TLS_HASHES_HIGH \
	MBEDTLS_SSL_HASH_SHA512,\
	MBEDTLS_MD_NONE

#define AEM_TLS_HASHES_OUT \
	MBEDTLS_SSL_HASH_SHA512,\
	MBEDTLS_SSL_HASH_SHA384,\
	MBEDTLS_SSL_HASH_SHA256,\
	MBEDTLS_MD_NONE
