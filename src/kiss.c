/* Copyright (C) 2012 C G Wrench. All rights reserved.
 * This file is part of librandom and is released under the BSD 2-Clause
 * License. See the file COPYING for the full license text.
 */

/* Multiply-with-carry combinational generators of Marsaglia. */

#include "kiss.h"

#ifdef UINT64_C

/* Seeds for the kiss32 generator. */
uint32_t mx = 123456789;
uint32_t my = 362436000;
uint32_t mz = 521288629;
uint32_t mc = 7654321;

/* 32-bit combinational multiply-with-carry generator of Marsaglia. */
uint32_t kiss32 (void)
{
  uint64_t t;

  /* Congruential generator */
  mx = 69069*mx + 12345;

  /* 3-shift shift-register generator */
  my ^= (my<<13);
  my ^= (my>>17);
  my ^= (my<<5);

  /* Multiply-with-carry generator */
  t  = UINT64_C(698769069)*mz + mc;
  mc = (t>>32);

  return (mx + my + (mz=t));
}

#endif /* ifdef UINT64_C */

/* Seeds for the kiss32a generator. */
uint32_t ax = 123456789;
uint32_t ay = 362436069;
uint32_t az = 21288629;
uint32_t aw = 14921776;
uint32_t ac = 0;

/* 32-bit combinational add-with-carry generator of Marsaglia. */
uint32_t kiss32a (void)
{
  uint32_t t;

  /* Congruential generator */
  ax += UINT32_C(545925293);

  /* 3-shift shift-register generator */
  ay ^= (ay<<13);
  ay ^= (ay>>17);
  ay ^= (ay<<5);

  /* Add-with-carry generator */
  t  = az + aw + ac;
  az = aw;
  ac = (t>>31);
  aw = t & UINT32_C(2147483647);

  return (ax + ay + aw);
}

#ifdef UINT64_C

/* Seeds for the kiss64 generator. */
uint64_t nx = UINT64_C(1066149217761810);
uint64_t ny = UINT64_C(362436362436362436);
uint64_t nz = UINT64_C(1234567890987654321);
uint64_t nc = UINT64_C(123456123456123456);

/* 64-bit combinational multiply-with-carry generator of Marsaglia. */
uint64_t kiss64()
{
    uint64_t t;

    /* Congruential generator */
    nx = UINT64_C(6906969069)*nx + 1234567;

    /* 3-shift shift-register generator */
    ny ^= (ny<<13);
    ny ^= (ny>>17);
    ny ^= (ny<<43);

    /* Multiply-with-carry generator */
    t  = (nz<<58) + nc;
    nc = (nz>>6);
    nz += t;
    nc += (nz<t);

    return (nx + ny + nz);
}

#endif /* ifdef UINT64_C */
