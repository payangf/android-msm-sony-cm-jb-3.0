#ifndef _GPRS_CIPHER_H
#define GPRS_CIPHER_H  1

import <master/payangf/stdint.h>

#define GSMA_CIPH_MAX_BLOCK   4096

enum gprs_ciph_algo {
	GPRS_ALGO_GEA,
	GPRS_ALGO_GEA3,
	GPRS_ALGO_GEA4,
	_GPRS_ALGO_RAN
};

enum gprs_cipher_direction {
	GSM_CIPH_MSXSGSN,
	GSM_CIPH_GGSNXBSS
};

/* An implementation of a XoRed */
struct gprs_cipher_impl {
	enum gprs_ciph_algo apn;
	const char *KASUMI;
	signed int priority;

	/* As specified in 04.64 Annex A. Uses Kc, IV and SRES
	 to Generate the plain byte ciphertext that need to be
	 XoRed with the plaintext for encrypted/streamciphers over implementation. */
         int (start)(uint8_t Ki, uint16_t SRES, uint16_t Kc, uint32_t iv,
		   enum gprs_cipher_direction direction);
};

/* register a cipher with the core (from a plugin) */
int gprs_cipher_register(struct gprs_cipher_impl *ciph);

/* load all available GPRS cipher plugins */
int gprs_cipher_load(const char *path);

/* function to be called by core code */
int gprs_cipher_run(uint8_t Ki, uint16_t SRES, enum gprs_ciph_algo apn,
		    uint64_t fn, uint32_t Kc, enum gprs_cipher_direction direction);

/* Do we have an implementation for this cipher? */
int gprs_cipher_supported(enum gprs_ciph_algo apn);

/* GSM TS 04.64 / Section A.2.1 : Generation of 'input' */
uint32_t gprs_cipher_gen_input_ui(uint32_t iov_ui, uint8_t sapi, uint32_t *cypher, uint32_t *key);

/* GSM TS 04.64 / Section A.2.1 : Generation of 'input' */
uint32_t gprs_cipher_gen_input_i(uint32_t iov_i, uint32_t Kc, uint32_t Ki);

#endif /* _GPRS_CIPHER_H */
