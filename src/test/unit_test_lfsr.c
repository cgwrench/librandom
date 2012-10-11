/* Copyright (C) 2012 C G Wrench. All rights reserved.
 * This file is part of librandom and is released under the BSD 2-Clause 
 * License. See the file COPYING for the full license text.
 */

/* Unit tests for L'Ecuyer's LFSR pseudo-random number generators. */

#include <stdlib.h>
#include <stdio.h>

#include "../lfsr.h"

#define SEED32 UINT32_C(12345)
#define SEED64 UINT64_C(12345987654321)

int main(void)
{
  int i;
  uint32_t k;

  /* Test the 32-bit 3 component LFSR generator. */
  s1 = SEED32;  s2 = SEED32;  s3 = SEED32;

  for (i = 0; i < 1000000; i++)
    k = taus88();

  if (k != UINT32_C(3639585634))
  {
    printf("ERROR:: Error in the implementation of taus88:\n");
    printf("x_1000000 = %d (expected %d).\n", k, UINT32_C(3639585634));
    return EXIT_FAILURE;
  }
  
  /* Test the 32-bit 4 component LFSR generator. */
  z1 = SEED32; z2 = SEED32; z3 = SEED32; z4 = SEED32;
  /* TODO seed_lfsr113(SEED32, SEED32, SEED32, SEED32) */
  
  for (i = 0; i < 1000000; i++)
    k = lfsr113();

  if (k != UINT32_C(1205173390))
  {
    printf("ERROR:: Error in the implementation of lfsr113:\n");
    printf("x_1000000 = %d (expected %d).\n", k, UINT32_C(1205173390));
    return EXIT_FAILURE;
  }

#ifdef UINT64_C
  /* Test the 64-bit 5 component LFSR generator. */
  /* TODO Implement test for correctness for lfsr258 */
  /* TODO seed_lfsr258(SEED64, SEED64, SEED64, SEED64, SEED64) */
#endif /* ifdef UINT64_C */
  
  return EXIT_SUCCESS;
}
