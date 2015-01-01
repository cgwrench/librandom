/* Copyright (C) 2012-2015, C G Wrench. All rights reserved.
 * This file is part of librandom and is released under the BSD 2-Clause
 * License. See the file COPYING for the full license text.
 */

/* Unit tests for Marsaglia's KISS pseudo-random number generators. */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../src/kiss.h"

#undef NDEBUG
#define _unused(x) (void)(x)

int main(void)
{
  uint32_t j;

  /* Test the 32-bit add-with-carry kiss generator. */
  kiss32a_state_t * kiss32a_state;
  kiss32a_state = (kiss32a_state_t*) malloc(sizeof(kiss32a_state_t));

  kiss32a_state->mx = UINT32_C(123456789);
  kiss32a_state->my = UINT32_C(362436069);
  kiss32a_state->mz = UINT32_C(21288629);
  kiss32a_state->mw = UINT32_C(14921776);
  kiss32a_state->mc = UINT32_C(0);
  /* TODO kiss32a_state_t * seed_kiss32a(kiss32a_t *state, uint32_t mx,
       uint32_t my, uint32_t mz, uint32_t mw, uint32_t mc);
     Populate state (malloc if required). If NULL pointer returned, not
     successful.
  */

  /* Note, the following test corrects the original Usenet posting (Fortran and
     C: United with a kiss) of Marsaglia: we use 100000, not 10000 iterations.
   */
  for (int i = 0; i < 99996; i++)
  {
    _unused(j = kiss32a(kiss32a_state));
  }

  /* Test next four values for correctness */
  assert(kiss32a(kiss32a_state) == UINT32_C( 199275006));
  assert(kiss32a(kiss32a_state) == UINT32_C(  86473693));
  assert(kiss32a(kiss32a_state) == UINT32_C(2209597521));
  assert(kiss32a(kiss32a_state) == UINT32_C(1298124039));

#ifdef UINT64_C
  uint64_t k;

  /* Test the 32-bit multiply-with-carry kiss generator. */
  kiss32_state_t * kiss32_state;
  kiss32_state = (kiss32_state_t*) malloc(sizeof(kiss32_state_t));

  kiss32_state->mx = UINT32_C(123456789);
  kiss32_state->my = UINT32_C(362436000);
  kiss32_state->mz = UINT32_C(521288629);
  kiss32_state->mc = UINT32_C(7654321);
  /* TODO kiss32_state_t * seed_kiss32(kiss32_t *state, uint32_t mx,
       uint32_t my, uint32_t mz, uint32_t mc);
     Populate state (malloc if required). If NULL pointer returned, not
     successful.
  */

  for (int i = 0; i < 1000000; i++)
  {
    _unused(j = kiss32(kiss32_state));
  }

  /* The following test is from simplerandom, see
   * https://bitbucket.org/cmcqueen1975/simplerandom/wiki/Home */
  assert(j == UINT32_C(1010846401));

  /* Test the 64-bit multiply-with-carry kiss generator. */
  kiss64_state_t * kiss64_state;
  kiss64_state = (kiss64_state_t*) malloc(sizeof(kiss64_state_t));

  kiss64_state->mx = UINT64_C(1066149217761810);
  kiss64_state->my = UINT64_C(362436362436362436);
  kiss64_state->mz = UINT64_C(1234567890987654321);
  kiss64_state->mc = UINT64_C(123456123456123456);
  /* TODO kiss64_state_t * seed_kiss64(kiss64_t *state, uint64_t mx,
       uint64_t my, uint64_t mz, uint64_t mc);
     Populate state (malloc if required). If NULL pointer returned, not
     successful.
  */

  for (int i = 0; i < 100000000; i++)
  {
    _unused(k = kiss64(kiss64_state));
  }

  assert(k == UINT64_C(1666297717051644203));

#endif /* ifdef UINT64_C */

  return EXIT_SUCCESS;
}

