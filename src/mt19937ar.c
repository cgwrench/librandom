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
 * Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
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
 * Modified from the reference implementation, available from
 * <http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/MT2002/emt19937ar.html>,
 * by Chris Wrench, 12/10/12, as follows:
 *  - Unused functions genrand_real1, genrand_real2, genrand_real2 and
 *    genrand_res53 removed and example test code moved to separate test
 *    file (see files under ./test/).
 *  - genrand_int32() renamed mt19937().
 *  - Integer type definitions replaced with C99 fixed width integers, as
 *    defined in <stdint.h>.
 *  - Principal computational lines left untouched.
 *  - Still to do: define a state type (see below).
 */

#include "mt19937ar.h"

/* Parameters which determine the period of the generator -- don't change. */
#define N INT32_C(624)
#define M INT32_C(397)
#define MATRIX_A INT32_C(0x9908b0df)   /* Constant vector a */
#define UPPER_MASK INT32_C(0x80000000) /* Most significant w-r bits */
#define LOWER_MASK INT32_C(0x7fffffff) /* Least significant r bits */

/* TODO Define state type:
typedef struct {
  uint32_t state[N]; / * State vector. * /
  int index; / * State index: mti==N+1 means state[N] is not initialized. * /
} MT19937_state;
*/

static uint32_t mt[N]; /* State vector. */
static int mti=N+1; /* State index: mti==N+1 means mt[N] is not initialized */

/* Core 32-bit Mersenne Twister generator. */
uint32_t mt19937ar (void)
{
    uint32_t y;
    static uint32_t mag01[2]={INT32_C(0x0), MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= N) /* Generate N words at once. */
    {
      int kk;

      for (kk=0; kk<N-M; kk++)
      {
        y = (mt[kk] & UPPER_MASK) | (mt[kk+1] & LOWER_MASK);
        mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & INT32_C(0x1)];
      }

      for (; kk<N-1; kk++)
      {
        y = (mt[kk] & UPPER_MASK) | (mt[kk+1] & LOWER_MASK);
        mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & INT32_C(0x1)];
      }

      y = (mt[N-1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
      mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & INT32_C(0x1)];

      mti = 0;
    }

    y = mt[mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y <<  7) & INT32_C(0x9d2c5680);
    y ^= (y << 15) & INT32_C(0xefc60000);
    y ^= (y >> 18);

    return y;
}

/* Initialise seed state mt[N] with a scalar seed. */
void init_mt19937ar (uint32_t s)
{
  mt[0] = s & INT32_C(0xffffffff);
  for (mti=1; mti<N; mti++)
  {
    mt[mti] = (INT32_C(1812433253) * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti);
      /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
      /* In the previous versions, MSBs of the seed affect   */
      /* only MSBs of the array mt[].                        */
      /* 2002/01/09 modified by Makoto Matsumoto             */
    mt[mti] &= INT32_C(0xffffffff);
      /* For >32 bit machines. Unnecessary with fixed width integers? */
  }
}

/* Initialise seed state mt[N] with an array.
 * init_key is the array for initializing keys, key_length is it's length.
 */
void init_mt19937ar_by_array (uint32_t init_key[], int key_length)
{
  int i, j, k;

  init_mt19937ar(INT32_C(19650218));
  i=1; j=0;
  k = (N>key_length ? N : key_length);

  for (; k; k--)
  {
    mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * INT32_C(1664525)))
          + init_key[j] + j; /* non linear */
    mt[i] &= INT32_C(0xffffffff); /* for WORDSIZE > 32 machines */
                                  /* Unnecessary with fixed width integers? */
    i++; j++;
    if (i>=N) { mt[0] = mt[N-1]; i=1; }
    if (j>=key_length) j=0;
  }

  for (k=N-1; k; k--)
  {
    mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * INT32_C(1566083941)))
          - i; /* non linear */
    mt[i] &= INT32_C(0xffffffff); /* for WORDSIZE > 32 machines */
                                  /* Unnecessary with fixed width integers? */
    i++;
    if (i>=N) { mt[0] = mt[N-1]; i=1; }
  }

  mt[0] = INT32_C(0x80000000); /* MSB is 1; assuring non-zero initial array */
}
