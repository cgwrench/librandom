/* Copyright (C) 2012-2015, C G Wrench. All rights reserved.
 * This file is part of librandom and is released under the BSD 2-Clause
 * License. See the file COPYING for the full license text.
 */

/* Multiply-with-carry combinational generators of Marsaglia.
 *
 * The kiss family of pseudo-random number generators are combinational
 * generators developed by George Marsaglia. Generally kiss generators are
 * comprised of three generators: a linear congruential generator, a 3-shift
 * generator and either a multiply-with-carry (MWC) or a complimentary
 * multiply-with-carry (CMWC) generator. Broadly speaking Marsaglia's kiss
 * principle refers to the use of multiple different types of generators
 * combined to yield 'better' results than would be obtained using each
 * generator individually.
 *
 * The kiss generators were developed over a number of years and through
 * lengthy discussions across many Usenet newsgroups. The result is a highly
 * efficient pseudo-random number generator with large period, portable
 * implementations in both C and Fortran (amongst numerous other languages)
 * and which passes all known tests for randomness.
 *
 * It should be noted that in the original UseNet postings by George Marsaglia
 * many variables were defined to be (unsigned) long, with the assumption made
 * that these variables were 32-bits wide. However, on many systems long is in
 * fact 64-bits wide, which leads to different sequences of random numbers
 * between these systems.
 *
 * In the following implementations C99 standard fixed width integer types,
 * defined in <stdint.h>, are used. This allows us to be explicit with the
 * required width in bits of each variable and increases the poratability of
 * the implementations.
 *
 * See:
 *  - Marsaglia, G, Random Number Generators, Journal of Modern Applied
 *    Statistical Methods 2, 2-13 (2003)
 *  - George Marsaglia <g...@stat.fsu.edu> KISS random number generator,
 *    Article <> in Usenet newsgroup: sci.math.num-analysis, 17 January 2003
 *  - George Marsaglia <g...@stat.fsu.edu> RNGs, Article <> in Usenet
 *    newsgroup: sci.math, 25 February 2003.
 */

#ifndef KISS_H_
#define KISS_H_

#include <stdint.h>

#ifdef UINT64_MAX

/* State type for the kiss32 generator. */
typedef struct {
  uint32_t mx, my, mz, mc;
} kiss32_state_t;

/* Return a 32-bit integer drawn from the uniform distribution on [0, 2^32 - 1].
 *
 * The 32-bit kiss generator pseudo-random number, combining:
 *  - the congruential generator x_n = 69069 x_{n-1} + 12345, period 2^32;
 *  - a 3-shift shift-register generator, period 2^32 - 1;
 *  - a 32-bit multiply-with-carry generator, period (698769069 2^21)-1 > 2^59.
 *
 * The overall period is thus 2^32 (2^32 - 1) ((698769069 2^31)-1) > 2^123
 * ~ 2x10^37.
 *
 * The seeds mx, my, mz and mc must be set before calling this routine and
 * **must** be within the ranges 0 <= mx < 2^32, 0 < my < 2^32,
 * 0 <= mz < 2^32 and 0<= mc < 698769069 respectively.
 *
 * Note: this implementation depends on unsigned 64-bit arithmetic. Use kiss32a
 * on systems without a 64-bit integer data type.
 *
 * This implementation corrects a number of mistakes present in implementations
 * presented elsewhere. Earlier implementations are dismissed as flawed, since
 * either the particular implmenentations of the generator have since been
 * shown to be incorrect or they were listed without tests for correctness.
 * For example, the 3-shift shift-register generator listed in
 *
 *   George Marsaglia <g...@stat.fsu.edu> Random Numbers for C: End, at last?,
 *   Article <> in Usenet newsgroup: sci.stat.math and others, 21 Jan 1999
 *
 * has been shown to not have the stated period of 2^32 - 1 but instead has
 * 64 cycles, some with very short periods. This 3-shift generator is very
 * similar to the listing
 *
 *   Marsaglia, G, Random Number Generators, Journal of Modern Applied
 *   Statistical Methods 2, 2-13 (2003)
 *
 * but with two shift values swapped, suggesting that the 1999 implementation
 * contains a typo.
 *
 * See: Marsaglia, G, Random Number Generators, Journal of Modern Applied
 *      Statistical Methods 2, 2-13 (2003)
 */
uint32_t kiss32 (kiss32_state_t *state);

#endif /* ifdef UINT64_MAX */

/* State type for the kiss32a generator. */
typedef struct {
  uint32_t mx, my, mz, mw, mc;
} kiss32a_state_t;

/* Return a 32-bit integer drawn from the uniform distribution on [0, 2^32 - 1].
 *
 * Implementation of a 32-bit KISS generator which uses no multiply
 * instructions. This is the add-with-carry combinational generator of
 * Marsaglia. The standard 32-bit version of kiss (kiss32, above) requires
 * unsigned 64-bit arithmetic. kiss32a is designed to avoid this, and can thus
 * be used on systems without a 64-bit integer data type.
 *
 * The overall period is 576384491062058838 * 4294967296 * 4294967295 or
 * approximately 2^121 ~ 10^36.

 * The seeds ax, ay, az, aw and ac must be set before calling this routine and
 * **must** be within the ranges 0 <= ax < 2^32, 0 < ay < 2^32,
 * 0 <= az < 2^31, 0 < aw < 2^31. Furthermore, ac can be 0 or 1 and az and aw
 * must not be mutiples of 7559.
 *
 * See: George Marsaglia <g...@stat.fsu.edu> Fortran and C: United with a KISS,
 *      Article <> in Usenet newsgroup: comp.lang.fortran, 23 June 2007.
 */
uint32_t kiss32a (kiss32a_state_t *state);

#ifdef UINT64_MAX

/* State type for the kiss64 generator. */
typedef struct {
  uint64_t mx, my, mz, mc;
} kiss64_state_t;

/* Return a 64-bit integer drawn from the uniform distribution on [0, 2^64 - 1].
 *
 * The 64-bit kiss generator pseudo-random number, combining:
 *  - the congruential generator x_n = 6906969069x_{n-1} + 1234567, period 2^64;
 *  - a 3-shift shift-register generator, period 2^64 - 1;
 *  - a 64-bit multiply-with-carry generator, period ...
 *
 * TODO The overall period is thus... approximately 2^250 ~ 10^74.
 * TODO The seeds nx, ny, nz and nc must be set before calling this routine and
 * **must** be... (64 bits each for of nx, ny, nz and 58-bits for nc).
 *
 * See: George Marsaglia <gmarsag...@gmail.com> 64-bit KISS RNGs, Article <> in
 * Usenet newsgroups: sci.math, comp.lang.c, comp.lang.fortran, 28
 * February 2009.
 */
uint64_t kiss64 (kiss64_state_t *state);

#endif /* ifdef UINT64_MAX */

#endif /* KISS_H_ */
