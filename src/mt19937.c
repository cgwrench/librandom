/* Copyright (C) 2012 C G Wrench. All rights reserved.
 * This file is part of librandom and is released under the BSD 2-Clause
 * License. See the file COPYING for the full license text.
 *
 * This code is modified from the reference implementation of the Mersenne
 * Twister algorithm available from
 * <http://www.math.keio.ac.jp/~matumoto/MT2002/emt19937ar.html>, originally
 * released under the 3-clause, Modified BSD License, included verbatim from
 * the original code below:
 *
 * Copyright (C) 1997 - 2002, 2004, Makoto Matsumoto and Takuji Nishimura,
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *
 *   3. The names of its contributors may not be used to endorse or promote
 *      products derived from this software without specific prior written
 *      permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* Mersenne Twister MT19937ar generator of Matsumoto and Nishimura.
 *
 * Modified from the reference implementations, available from
 * <http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/MT2002/emt19937ar.html>
 * and <http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt64.html>,
 * by Chris Wrench, 12/10/12, as follows:
 *
 *  - Principal computational lines left untouched.
 *  - Integer type definitions replaced with C99 fixed width integers, as
 *    defined in <stdint.h>. This eliminates the need for some bit masks
 *    in the 32-bit Mersenne Twister.
 *  - `genrand_int32` renamed `mt19937ar`.
 *  - `init_genrand` renamed `init_mt19937ar` and `init_by_array`
 *    renamed `init_mt19937ar_by_array`.
 *  - `genrand_int64` renamed `mt19937_32`.
 *  - `init_genrand64` renamed `init_mt19937_64` and `init_by_array64`
 *    renamed `init_mt19937_64_by_array`.
 *  - Unused 32-bit functions `genrand_int31`, `genrand_real1`, `genrand_real2`,
 *    `genrand_real2` and `genrand_res53` removed and example test code moved
 *    to separate test file (see files under ./test/).
 *  - Unused 64-bit functions `genrand64_real1`, `genrand64_real2` and
 *    `genrand64_real2` removed.
 *  - Still to do: define a state type (see below).
 */

#include "mt19937.h"

/* Parameters which determine period of the 32-bit generator - don't change. */
#define N INT32_C(624)
#define M INT32_C(397)
#define MATRIX_A UINT32_C(0x9908b0df)   /* Constant vector a */
#define UPPER_MASK UINT32_C(0x80000000) /* Most significant w-r bits */
#define LOWER_MASK UINT32_C(0x7fffffff) /* Least significant r bits */

/* TODO Define a state type:
typedef struct {
  uint32_t state[N]; / * State vector. * /
  int index; / * State index: mti==N+1 means state[N] is not initialized. * /
} MT19937_state_t;
*/

static uint32_t mt[N]; /* State vector. */
static int mti=N+1; /* State index: mti==N+1 means mt[N] is not initialized */

/* Core 32-bit Mersenne Twister generator. */
uint32_t mt19937ar (void)
{
    uint32_t y;
    static uint32_t mag01[2]={UINT32_C(0x0), MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= N) /* Generate N words at once. */
    {
      int kk;

      for (kk=0; kk<N-M; kk++)
      {
        y = (mt[kk] & UPPER_MASK) | (mt[kk+1] & LOWER_MASK);
        mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & UINT32_C(0x1)];
      }

      for (; kk<N-1; kk++)
      {
        y = (mt[kk] & UPPER_MASK) | (mt[kk+1] & LOWER_MASK);
        mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & UINT32_C(0x1)];
      }

      y = (mt[N-1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
      mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & UINT32_C(0x1)];

      mti = 0;
    }

    y = mt[mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y <<  7) & UINT32_C(0x9d2c5680);
    y ^= (y << 15) & UINT32_C(0xefc60000);
    y ^= (y >> 18);

    return y;
}

/* Initialise seed state mt[N] with a scalar seed. */
void init_mt19937ar (uint32_t seed)
{
  mt[0] = seed & UINT32_C(0xffffffff);
  for (mti=1; mti<N; mti++)
  {
    mt[mti] = (UINT32_C(1812433253) * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti);
      /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
      /* In the previous versions, MSBs of the seed affect   */
      /* only MSBs of the array mt[].                        */
      /* 2002/01/09 modified by Makoto Matsumoto             */
  }
}

/* Initialise seed state mt[N] with an array.
 * init_key is the array for initializing keys, key_length is it's length.
 */
void init_mt19937ar_by_array (uint32_t init_key[], int key_length)
{
  int i, j, k;

  init_mt19937ar(UINT32_C(19650218));
  i=1; j=0;
  k = (N>key_length ? N : key_length);

  for (; k; k--)
  {
    mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * UINT32_C(1664525)))
          + init_key[j] + j; /* non linear */

    i++; j++;
    if (i>=N) { mt[0] = mt[N-1]; i=1; }
    if (j>=key_length) j=0;
  }

  for (k=N-1; k; k--)
  {
    mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * UINT32_C(1566083941)))
          - i; /* non linear */
    i++;
    if (i>=N) { mt[0] = mt[N-1]; i=1; }
  }

  mt[0] = UINT32_C(0x80000000); /* MSB is 1; assuring non-zero initial array */
}

#ifdef UINT64_C

/* Parameters which determine period of the 64-bit generator - don't change. */
#define NN 312
#define MM 156
#define MATRIX_AA UINT64_C(0xB5026F5AA96619E9)
#define UM UINT64_C(0xFFFFFFFF80000000) /* Most significant 33-bits. */
#define LM UINT64_C(0x7FFFFFFF)         /* Least significant 31-bits. */

/* TODO Define a state type: */
static uint64_t mt64[NN]; /* State vector. */
static int mt64i=NN+1; /* State index: mt64i==NN+1 means mt64[NN] is not initialized */

/* Core 64-bit Mersenne Twister generator. */
uint64_t mt19937_64 (void)
{
    uint64_t x;
    static uint64_t mag01[2]={UINT64_C(0), MATRIX_AA};

    if (mt64i >= NN) /* Generate NN words at once. */
    {
      int i;

      for (i=0; i<NN-MM; i++)
      {
        x = (mt64[i] & UM) | (mt64[i+1] & LM);
        mt64[i] = mt64[i+MM] ^ (x >> 1) ^ mag01[(int)(UINT64_C(x&1))];
      }

      for (; i<NN-1; i++)
      {
        x = (mt64[i] & UM) | (mt64[i+1] & LM);
        mt64[i] = mt64[i+(MM-NN)] ^ (x >> 1) ^ mag01[(int)(UINT64_C(x&1))];
      }

      x = (mt64[NN-1] & UM) | (mt64[0] & LM);
      mt64[NN-1] = mt64[MM-1] ^ (x >> 1) ^ mag01[(int)(UINT64_C(x&1))];

      mt64i = 0;
    }

    x = mt64[mt64i++];

    /* Tempering */
    x ^= (x >> 29) & UINT64_C(0x5555555555555555);
    x ^= (x << 17) & UINT64_C(0x71D67FFFEDA60000);
    x ^= (x << 37) & UINT64_C(0xFFF7EEE000000000);
    x ^= (x >> 43);

    return x;
}

/* Initialise seed state mt64[N] with a scalar seed. */
void init_mt19937_64 (uint32_t seed)
{
  mt64[0] = seed;
  for (mt64i=1; mt64i<NN; mt64i++)
  {
    mt64[mt64i] = (UINT64_C(6364136223846793005)
      * (mt64[mt64i-1] ^ (mt64[mt64i-1] >> 62)) + mt64i);
  }
}

/* Initialise seed state mt64[NN] with an array.
 * init_key is the array for initializing keys, key_length is it's length.
 */
void init_mt19937_64_by_array (uint64_t init_key[], int key_length)
{
  int i, j, k;

  init_mt19937_64(UINT64_C(19650218));
  i=1; j=0;
  k = (NN>key_length ? NN : key_length);

  for (; k; k--)
  {
    mt64[i] = (mt64[i] ^ ((mt64[i-1] ^ (mt64[i-1] >> 62))
          * UINT64_C(3935559000370003845)))
          + init_key[j] + j; /* non linear */
    i++; j++;
    if (i>=NN) { mt64[0] = mt64[NN-1]; i=1; }
    if (j>=key_length) j=0;
  }

  for (k=NN-1; k; k--)
  {
    mt64[i] = (mt64[i] ^ ((mt64[i-1] ^ (mt64[i-1] >> 62))
       * UINT64_C(2862933555777941757)))
       - i; /* non linear */
    i++;
    if (i>=NN) { mt64[0] = mt64[NN-1]; i=1; }
  }

  mt64[0] = UINT64_C(1) << 63; /* MSB is 1; assuring non-zero initial array */
}

#endif /* ifdef UINT64_C */

