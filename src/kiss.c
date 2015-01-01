/* Copyright (C) 2012-2015, C G Wrench. All rights reserved.
 * This file is part of librandom and is released under the BSD 2-Clause
 * License. See the file COPYING for the full license text.
 */

/* Multiply-with-carry combinational generators of Marsaglia. */

#include "kiss.h"

#ifdef UINT64_C

/* 32-bit combinational multiply-with-carry generator of Marsaglia. */
uint32_t kiss32 (kiss32_state_t *state)
{
  uint64_t t;

  /* Congruential generator */
  state->mx = 69069*state->mx + 12345;

  /* 3-shift shift-register generator */
  state->my ^= (state->my << 13);
  state->my ^= (state->my >> 17);
  state->my ^= (state->my <<  5);

  /* Multiply-with-carry generator */
  t  = UINT64_C(698769069)*state->mz + state->mc;
  state->mc = (t >> 32);

  return (state->mx + state->my + (state->mz=t));
}

#endif /* ifdef UINT64_C */

/* 32-bit combinational add-with-carry generator of Marsaglia. */
uint32_t kiss32a (kiss32a_state_t *state)
{
  uint32_t t;

  /* Congruential generator */
  state->mx += UINT32_C(545925293);

  /* 3-shift shift-register generator */
  state->my ^= (state->my << 13);
  state->my ^= (state->my >> 17);
  state->my ^= (state->my <<  5);

  /* Add-with-carry generator */
  t  = state->mz + state->mw + state->mc;
  state->mz = state->mw;
  state->mc = (t >> 31);
  state->mw = t & UINT32_C(2147483647);

  return (state->mx + state->my + state->mw);
}

#ifdef UINT64_C

/* 64-bit combinational multiply-with-carry generator of Marsaglia. */
uint64_t kiss64 (kiss64_state_t *state)
{
    uint64_t t;

    /* Congruential generator */
    state->mx = UINT64_C(6906969069)*state->mx + 1234567;

    /* 3-shift shift-register generator */
    state->my ^= (state->my << 13);
    state->my ^= (state->my >> 17);
    state->my ^= (state->my << 43);

    /* Multiply-with-carry generator */
    t = (state->mz << 58) + state->mc;
    state->mc = (state->mz >>  6);
    state->mz += t;
    state->mc += (state->mz < t);

    return (state->mx + state->my + state->mz);
}

#endif /* ifdef UINT64_C */
