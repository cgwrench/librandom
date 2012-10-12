/* Copyright (C) 2012 C G Wrench. All rights reserved.
 * This file is part of librandom and is released under the BSD 2-Clause
 * License. See the file COPYING for the full license text.
 */

/* Unit tests for Marsaglia's KISS pseudo-random number generators. */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../kiss.h"

#undef NDEBUG

int main(void)
{
  uint32_t j;
  uint64_t k;

  /* Test the 32-bit add-with-carry kiss generator. */
  ax = 123456789; ay = 362436069; az = 21288629; aw = 14921776; ac = 0;
  /* TODO seed_kiss32a(...) */

  /* Note, the following test corrects the original Usenet posting (Fortran and
     C: United with a kiss) of Marsaglia, we use 100000, not 10000 iterations.
   */
  for (int i = 0; i < 99996; i++)
    j = kiss32a();

  /* Test next four values for correctness */
  assert(kiss32a() == UINT32_C( 199275006));
  assert(kiss32a() == UINT32_C(  86473693));
  assert(kiss32a() == UINT32_C(2209597521));
  assert(kiss32a() == UINT32_C(1298124039));

#ifdef UINT64_C

  /* Test the 32-bit multiply-with-carry kiss generator. */
  mx = UINT32_C(123456789); my = UINT32_C(362436000);
  mz = UINT32_C(521288629); mc = UINT32_C(7654321);

  for (int i = 0; i < 1000000; i++)
    j = kiss32();

  /* The following test is from
     [simplerandom](https://bitbucket.org/cmcqueen1975/simplerandom/wiki/Home).
   */
  assert(j == UINT32_C(1010846401));

  /* Test the 64-bit multiply-with-carry kiss generator. */
  nx = UINT64_C(1066149217761810);    ny = UINT64_C(362436362436362436);
  nz = UINT64_C(1234567890987654321); nc = UINT64_C(123456123456123456);
  /* TODO seed_kiss64(...) */

  for (int i = 0; i < 100000000; i++)
    k = kiss64();

  assert(k == UINT64_C(1666297717051644203));

#endif /* ifdef UINT64_C */

  return EXIT_SUCCESS;
}

