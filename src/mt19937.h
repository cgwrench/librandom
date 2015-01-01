/* Copyright (C) 2012-2015, C G Wrench. All rights reserved.
 * This file is part of librandom and is released under the BSD 2-Clause
 * License. See the file COPYING for the full license text.
 */

/* The Mersenne Twister generator of Matsumoto and Nishimura.
 *
 * The Mersenne Twister is a pseudo-random number generator developed by
 * M. Matsumoto and T. Nishimura. The standard Mersenne Twister, MT19937, has
 * a huge period of 2^{19937} - 1 and is fast. The speed of the generator
 * comes from only updating a small part of the state of 624 longs (or
 * 19968 bits) for each pseudo-random number generated, and moving through
 * the state over multiple calls. The Mersenne Twister has become one of the
 * most extensively tested and widely used pseudo-random number generators
 * in existence.
 *
 * The reference implementation of the 32-bit Mersenne Twister 19937
 * algorithm is available from
 * <http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/MT2002/emt19937ar.html>
 * and the 64-bit reference implementation is available from
 * <http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt64.html>.
 *
 * See:
 *  - Matsumoto, M and Kurita, Y, *Twisted GFSR generators*, ACM Transactions
 *    on Modeling and Computer Simulation **2**, 179-94 (1992)
 *  - Matsumoto, M and Kurita, Y, *Twisted GFSR generators II*, ACM
 *    Transactions on Modeling and Computer Simulation **4**, 254-66 (1994)
 *  - Matsumoto, M and Nishimura, T, *Mersenne Twister: A 623- dimensionally
 *    equidistributed uniform pseudorandom number generator*, ACM Transactions
 *    on Modeling and Computer Simulation **8**, 3-30 (1998).
 *  - Nishimura, T, *Tables of 64-bit Mersenne Twisters*, ACM Transactions
 *    on Modeling and Computer Simulation **10**, 348--57 (2000).
 *
 * See also the [SIMD-oriented Fast Mersenne Twister
 * (SFMT)](http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/SFMT/index.html).
 *
 */

#ifndef MT19937_H_
#define MT19937_H_

#include <stdint.h>

/* Return a 32-bit pseudo-random integer on the interval [0,0xffffffff].
 *
 * The seed state **must** be initialised, using init_mt19937ar() or
 * init_mt19937ar_by_array(), before calling this routine.
 */
uint32_t mt19937ar (void);

/* mt19937ar initialisation routines. */
void init_mt19937ar (uint32_t seed);
void init_mt19937ar_by_array (uint32_t init_key[], int key_length);

#ifdef UINT64_C

/* Return a 64-bit pseudo-random integer on the interval [0, 2^64 - 1].
 *
 * The seed state **must** be initialised, using init_mt19937_64() or
 * init_mt19937_64_by_array(), before calling this routine.
 */
uint64_t mt19937_64 (void);

/* mt19937_64 initialisation routines. */
void init_mt19937_64 (uint32_t seed);
void init_mt19937_64_by_array (uint64_t init_key[], int key_length);

#endif /* ifdef UINT64_C */

#endif /* MT19937_H_ */
