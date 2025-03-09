#ifndef RSA_H
#define RSA_H

#if defined(WITH_RSA_OPENSSL)
#include <openssl/bn.h>

struct rsa {
	BN_CTX *ctx;
	BIGNUM *exponent;
	BIGNUM *modulus;
};

#elif defined(WITH_RSA_LIBTOM)
#include <tommath.h>

struct rsa {
	mp_int exponent;
	mp_int modulus;
};
#elif defined(WITH_RSA_TINY)
#include <bn.h>

struct rsa {
	struct bn exponent;
	struct bn modulus;
};
#endif

int rsa_init(struct rsa *, const char *, const char *);
int rsa_decrypt(struct rsa *, void *, size_t, void *, size_t);
#endif
