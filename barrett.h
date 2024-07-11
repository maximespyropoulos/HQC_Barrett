#include <stdio.h> 
#include <string.h>
#include <inttypes.h>
#include "xoshiro256starstar.h"

#define D 1

void boolean_refresh(uint64_t *x);
void fisher_yates(uint64_t x[][D+1], uint16_t s, uint64_t n, uint16_t bits);
void boolean_demi_mult(uint64_t x[D+1], uint64_t y, uint64_t z[D+1], uint8_t bits);
void sec_equality(uint64_t x[D+1], uint64_t y[D+1], uint64_t z[D+1]);
void boolean_demi_sec_plus(uint64_t x[D+1], uint64_t y, uint64_t z[D+1]);
void sec_if(uint64_t a[D+1], uint64_t b[D+1], uint64_t c[D+1], uint64_t res[D+1]);
void boolean_sec_plus(uint64_t *x, uint64_t *y, uint64_t *z);
