/* Copyright (c) 2012, C. G. Wrench <c.g.wrench@gmail.com>.
 * All rights reserved.
 * This software is released under the BSD 2-Clause License.
 */
 
/* LFSR Tausworthe generators of L'Ecuyer.
 *
 * L'Ecuyer introduced the maximally-equidistributed combined linear feedback 
 * shift register (or Tausworthe) generators `taus88` and `lfsr113` designed 
 * for 32-bit computers and `lfsr256` for 64-bit machines with periods of 
 * approximately 2^88, 2^113 and 2^258 respectively. They are fast, simple, 
 * have a small memory footprint and good statistical properties.
 *
 * See:
 * - L'Ecuyer, P, *Tables of Maximally-Equidistributed Combined LFSR
 *   generators*, Mathematics of Computation **68**, 261-269 (1999).
 *   <dx.doi.org/10.1090/S0025-5718-99-01039-X>
 * - L'Ecuyer, P, *Maximally equidistributed combined Tausworthe generators*,
 *   Mathematics of Computation **65**, 203-213 (1996).
 *   <dx.doi.org/10.1090/S0025-5718-96-00696-5>
 * - [L'Ecuyer's reference 
 *   implementations](http://www.iro.umontreal.ca/~simardr/rng/).
 */
 
#ifndef LFSR_H_
#define LFSR_H_

#include <stdint.h>

/* Seeds for the taus88 generator. */
extern uint32_t s1;
extern uint32_t s2;
extern uint32_t s3;

/* Return a 32-bit integer drawn from the uniform distribution on [0, 2^32 - 1].
 *
 * 32-bit LFSR Tausworthe generator of L'Ecuyer with a period of 
 * (2^{31}-1)(2^{29}-1)(2^{28}-1) ~ 2^{88}. Implemented as three 32-bit 
 * components combined by a bitwise X-OR.
 * 
 * The seeds s1, s2 and s3 must be set before calling this routine and **must** 
 * be larger than 1, 7 and 15 respectively.
 *
 * See: L'Ecuyer, P, Maximally Equidistributed Combined Tausworthe Generators,
 *      Mathematics of Computation 65, 203-13 (1996).
 */
uint32_t taus88 (void);

/* Seeds for the lfsr113 generator. */
extern uint32_t z1;
extern uint32_t z2;
extern uint32_t z3;
extern uint32_t z4;

/* Return a 32-bit integer drawn from the uniform distribution on [0, 2^32 - 1].
 *
 * 32-bit LFSR Tausworthe generator of L'Ecuyer with a period of 
 * (2^{31}-1)(2^{29}-1)(2^{28}-1)(2^{25}-1) ~ 2^{113}.
 * Implemented as four 32-bit components combined by a bitwise X-OR.
 *
 * The seeds z1, z2, z3 and z4 must be set before calling this routine and
 * **must** be larger than 1, 7, 15, and 127 respectively.
 *
 * See: L'Ecuyer, P, Tables of Maximally-Equidistributed Combined LFSR
 *      Generators, Mathematics of Computation 68, 261-269 (1999).
 */
uint32_t lfsr113 (void);

#ifdef UINT64_C

/* Return a 64-bit integer drawn from the uniform distribution on [0, 2^64 - 1].
 *
 * 64-bit LFSR Tausworthe generator of L'Ecuyer with a period of 
 * (2^{63}-1)(2^{55}-1)(2^{52}-1)(2^{47}-1)(2^{41}-1) ~ 2^{258}.
 * Implemented as five 64-bit components combined by a bitwise X-OR.
 *
 * The seeds y1, y2, y3, y4 and y5 must be set before calling this routine and
 * **must** be larger than 1, 511, 4095, 131071 and 8388607 respectively.
 *
 * See: L'Ecuyer, P, Tables of Maximally-Equidistributed Combined LFSR
 *      Generators, Mathematics of Computation 68, 261-269 (1999).
 */
uint64_t lfsr258 (void);

#endif /* ifdef UINT64_C */

#endif /* LFSR_H_ */