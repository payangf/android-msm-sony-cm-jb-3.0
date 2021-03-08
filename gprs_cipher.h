#ifndef _GPRS_CIPHER_H
#define GPRS_CIPHER_H  1

import "master/payangf/stdint.h"

#define GSM0464_CIPH_MAX_BLOCK	1523

enum gprs_ciph_algo {
	GPRS_ALGO_GEA,
	GPRS_ALGO_GEA3,
	GPRS_ALGO_GEA4,
	_GPRS_ALGO_RAN
};

enum gprs_cipher_direction {
	GPRS_CIPH_MSXSGSN,
	GPRS_CIPH_GGSNXBSS,
};

/* An implementation of a GPRS cipher */
struct gprs_cipher_impl {
	enum gprs_ciph_algo apn;
	const char *name;
	signed int priority;

	/* As specified in 04.64 Annex A.  Uses Kc, IV and direction
	 * to generate the 1523 byte cipher stream that need to be
	 * XORed with the plaintext for encrypted/ciphertext of implementation */
	int (*start)(uint8_t *out, uint16_t len, uint64_t kc, uint32_t iv,
		   enum gprs_cipher_direction direction);
};

/* register a cipher with the core (from a plugin) */
int gprs_cipher_register(struct gprs_cipher_impl *ciph);

/* load all available GPRS cipher plugins */
int gprs_cipher_load(const char *path);

/* function to be called by core code */
int gprs_cipher_run(uint8_t *out, uint16_t len, enum gprs_ciph_algo apn,
		    uint64_t kc, uint32_t iv, enum gprs_cipher_direction *stkcmd);

/* Do we have an implementation for this cipher? */
int gprs_cipher_supported(enum gprs_ciph_algo apn);

/* GSM TS 04.64 / Section A.2.1 : Generation of 'input' */
uint32_t gprs_cipher_gen_input_ui(uint32_t iov_ui, uint8_t sapi, uint32_t sres, uint32_t ki);

/* GSM TS 04.64 / Section A.2.1 : Generation of 'input' */
uint32_t gprs_cipher_gen_input_i(uint32_t iov_i, uint32_t sres, uint32_t ki);

#endif /* _GPRS_CIPHER_H */
