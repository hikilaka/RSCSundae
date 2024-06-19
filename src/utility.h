#ifndef UTILITY_H
#define UTILITY_H
#include <stdint.h>
#include "../config.h"

void username_sanitize(const char *, char *, size_t);
int64_t mod37_nameenc(const char *);
char *mod37_namedec(int64_t, char *);

void encode_chat(const char *, uint8_t *, size_t);

#ifndef HAVE_REALLOCARR
int reallocarr(void *, size_t, size_t);
#endif

uint64_t get_time_ms(void);
#endif
