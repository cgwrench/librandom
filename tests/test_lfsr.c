/* Copyright (C) 2012 C G Wrench. All rights reserved.
 * This file is part of librandom and is released under the BSD 2-Clause
 * License. See the file COPYING for the full license text.
 */

/* Unit tests for L'Ecuyer's LFSR pseudo-random number generators. */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../src/lfsr.h"

#undef NDEBUG

#define SEED32 UINT32_C(12345)
#define SEED64 UINT64_C(12345987654321)

int main(void)
{
  uint32_t k;

  /* Test the 32-bit 3 component LFSR generator. */
  taus88_state_t * taus88_state;
  taus88_state = (taus88_state_t*) malloc(sizeof(taus88_state_t));

  taus88_state->s1 = SEED32;
  taus88_state->s2 = SEED32;
  taus88_state->s3 = SEED32;
  /* TODO tauss88_state_t * seed_taus88(tauss88_t *state, uint32_t s1,
       uint32_t s2, uint32_t s3);
     Populate state (malloc if required). If NULL pointer returned, not
     successful.
  */

  for (int i = 0; i < 1000000; i++)
  {
    k = taus88(taus88_state);
  }

  assert(k == UINT32_C(3639585634));

  /* Test the 32-bit 4 component LFSR generator. */
  lfsr113_state_t * lfsr113_state;
  lfsr113_state = (lfsr113_state_t*) malloc(sizeof(lfsr113_state_t));

  lfsr113_state->s1 = SEED32; lfsr113_state->s2 = SEED32;
  lfsr113_state->s3 = SEED32; lfsr113_state->s4 = SEED32;
  /* TODO lfsr113_state_t * seed_lfsr113(lfsr113_t *state, uint32_t s1,
       uint32_t s2, uint32_t s3, uint32_t s4);
     Populate state (malloc if required). If NULL pointer returned, not
     successful.
  */

  for (int i = 0; i < 1000000; i++)
  {
    k = lfsr113(lfsr113_state);
  }

  assert(k == UINT32_C(1205173390));

#ifdef UINT64_C
  uint64_t j;

  /* Test the 64-bit 5 component LFSR generator. */
  lfsr258_state_t * lfsr258_state;
  lfsr258_state = (lfsr258_state_t*) malloc(sizeof(lfsr258_state_t));

  lfsr258_state->s1 = SEED64; lfsr258_state->s2 = SEED64;
  lfsr258_state->s3 = SEED64; lfsr258_state->s4 = SEED64;
  lfsr258_state->s5 = SEED64;
  /* TODO lfsr258_state_t * seed_lfsr258(lfsr258_t *state, uint64_t s1,
       uint64_t s2, uint64_t s3, uint64_t s4, uint64_t s5);
     Populate state (malloc if required). If NULL pointer returned, not
     successful.
  */

  for (int i = 0; i < 1000000; i++)
  {
    j = lfsr258(lfsr258_state);
  }

  assert(j == UINT64_C(2366542785984680056));

#endif /* ifdef UINT64_C */

  return EXIT_SUCCESS;
}

