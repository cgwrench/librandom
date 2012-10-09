/* LFSR Tausworthe generators of L'Ecuyer. */

#include "lfsr.h"

/* Seeds for the taus88 generator. */
uint32_t s1;
uint32_t s2;
uint32_t s3;

/* 32-bit 3-component LFSR Tausworthe generator of L'Ecuyer. */
uint32_t taus88 (void)
{
    uint32_t b;
    b  = (((s1 << 13) ^ s1) >> 19);
    s1 = (((s1 & UINT32_C(4294967294)) << 12) ^ b);
    b  = (((s2 << 2) ^ s2) >> 25);
    s2 = (((s2 & UINT32_C(4294967288)) << 4) ^ b);
    b  = (((s3 << 3) ^ s3) >> 11);
    s3 = (((s3 & UINT32_C(4294967280)) << 17) ^ b);
    return (s1 ^ s2 ^ s3);
}

/* Seeds for the lfsr113 generator. */
uint32_t z1;
uint32_t z2;
uint32_t z3;
uint32_t z4;

/* 32-bit 4-component LFSR Tausworthe generator of L'Ecuyer. */
uint32_t lfsr113 (void)
{
   uint32_t b;
   b  = ((z1 << 6) ^ z1) >> 13;
   z1 = ((z1 & UINT32_C(4294967294)) << 18) ^ b;
   b  = ((z2 << 2) ^ z2) >> 27; 
   z2 = ((z2 & UINT32_C(4294967288)) << 2) ^ b;
   b  = ((z3 << 13) ^ z3) >> 21;
   z3 = ((z3 & UINT32_C(4294967280)) << 7) ^ b;
   b  = ((z4 << 3) ^ z4) >> 12;
   z4 = ((z4 & UINT32_C(4294967168)) << 13) ^ b;
   return (z1 ^ z2 ^ z3 ^ z4);
}

/* Is the UINT64_C cast required by C99? I don't think so. */
#ifdef UINT64_C

/* Seeds for the lfsr258 generator. */
uint64_t y1;
uint64_t y2;
uint64_t y3;
uint64_t y4;
uint64_t y5;

/* 64-bit LFSR Tausworthe generator of L'Ecuyer. */
uint64_t lfsr258 (void)
{
   uint64_t b;
   b  = ((y1 << 1) ^ y1) >> 53;
   y1 = ((y1 & UINT64_C(18446744073709551614)) << 10) ^ b;
   b  = ((y2 << 24) ^ y2) >> 50;
   y2 = ((y2 & UINT64_C(18446744073709551104)) << 5) ^ b;
   b  = ((y3 << 3) ^ y3) >> 23;
   y3 = ((y3 & UINT64_C(18446744073709547520)) << 29) ^ b;
   b  = ((y4 << 5) ^ y4) >> 24;
   y4 = ((y4 & UINT64_C(18446744073709420544)) << 23) ^ b;
   b  = ((y5 << 3) ^ y5) >> 33;
   y5 = ((y5 & UINT64_C(18446744073701163008)) << 8) ^ b;
   return (y1 ^ y2 ^ y3 ^ y4 ^ y5);
}

#endif /* ifdef UINT64_C */