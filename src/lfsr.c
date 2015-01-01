/* Copyright (C) 2012-2015, C G Wrench. All rights reserved.
 * This file is part of librandom and is released under the BSD 2-Clause
 * License. See the file COPYING for the full license text.
 */

/* LFSR Tausworthe generators of L'Ecuyer. */

#include "lfsr.h"

/* 32-bit 3-component LFSR Tausworthe generator of L'Ecuyer. */
uint32_t taus88 (taus88_state_t *state)
{
  #define TAUSWORTHE(s,a,b,c,d) ((s&c)<<d) ^ (((s <<a) ^ s)>>b)

  state->s1 = TAUSWORTHE(state->s1, 13, 19, UINT32_C(4294967294), 12);
  state->s2 = TAUSWORTHE(state->s2,  2, 25, UINT32_C(4294967288),  4);
  state->s3 = TAUSWORTHE(state->s3,  3, 11, UINT32_C(4294967280), 17);

  return (state->s1 ^ state->s2 ^ state->s3);
}

/* 32-bit 4-component LFSR Tausworthe generator of L'Ecuyer. */
uint32_t lfsr113 (lfsr113_state_t *state)
{
   uint32_t b;

   b  = ((state->s1 <<  6) ^ state->s1) >> 13;
   state->s1 = ((state->s1 & UINT32_C(4294967294)) << 18) ^ b;

   b  = ((state->s2 <<  2) ^ state->s2) >> 27;
   state->s2 = ((state->s2 & UINT32_C(4294967288)) <<  2) ^ b;

   b  = ((state->s3 << 13) ^ state->s3) >> 21;
   state->s3 = ((state->s3 & UINT32_C(4294967280)) <<  7) ^ b;

   b  = ((state->s4 <<  3) ^ state->s4) >> 12;
   state->s4 = ((state->s4 & UINT32_C(4294967168)) << 13) ^ b;

   return (state->s1 ^ state->s2 ^ state->s3 ^ state->s4);
}

/* Is the UINT64_C cast required by C99? I don't think so. */
#ifdef UINT64_C

/* 64-bit LFSR Tausworthe generator of L'Ecuyer. */
uint64_t lfsr258 (lfsr258_state_t *state)
{
   uint64_t b;

   b  = ((state->s1 <<  1) ^ state->s1) >> 53;
   state->s1 = ((state->s1 & UINT64_C(18446744073709551614)) << 10) ^ b;

   b  = ((state->s2 << 24) ^ state->s2) >> 50;
   state->s2 = ((state->s2 & UINT64_C(18446744073709551104)) <<  5) ^ b;

   b  = ((state->s3 <<  3) ^ state->s3) >> 23;
   state->s3 = ((state->s3 & UINT64_C(18446744073709547520)) << 29) ^ b;

   b  = ((state->s4 <<  5) ^ state->s4) >> 24;
   state->s4 = ((state->s4 & UINT64_C(18446744073709420544)) << 23) ^ b;

   b  = ((state->s5 <<  3) ^ state->s5) >> 33;
   state->s5 = ((state->s5 & UINT64_C(18446744073701163008)) <<  8) ^ b;

   return (state->s1 ^ state->s2 ^ state->s3 ^ state->s4 ^ state->s5);
}

#endif /* ifdef UINT64_C */
