/* Copyright (C) 2012 C G Wrench. All rights reserved.
 * This file is part of librandom and is released under the BSD 2-Clause
 * License. See the file COPYING for the full license text.
 */

/* Unit tests for the Mersenne Twister pseudo-random number generators. */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <inttypes.h>

#include "debug.h"
#include "../src/mt19937.h"

#undef NDEBUG

/* File containing expected output for the first 1000 calls to mt19937ar(). */
const char EXPECTED_OUTPUT_32[] = "test_mt19937ar.output";

#ifdef UINT64_C
/* File containing expected output for the first 1000 calls to mt19937_64(). */
const char EXPECTED_OUTPUT_64[] = "test_mt19937_64.output";
#endif /* ifdef UINT64_C */

int main(void)
{
  FILE *fd;
  int length = 4;

  uint32_t j;
  uint32_t init32[4] = { UINT32_C(0x123), UINT32_C(0x234),
                         UINT32_C(0x345), UINT32_C(0x456) };
#ifdef UINT64_C
  uint64_t k;
  uint64_t init64[4] = { UINT64_C(0x12345), UINT64_C(0x23456),
                         UINT64_C(0x34567), UINT64_C(0x45678) };
#endif /* ifdef UINT64_C */

  /* Test the 32-bit Mersenne Twister generator. */
  init_mt19937ar_by_array(init32, length);

  fd = fopen(EXPECTED_OUTPUT_32, "r");
  if (fd == NULL)
  {
    log_error("Unable to open '%s'.", EXPECTED_OUTPUT_32);
    return EXIT_FAILURE;
  }

  /* Check for the correct first 1000 output values. */
  for (int i = 0; i < 1000; i++)
  {
    if (fscanf(fd, "%"PRIu32"", &j) != 1)
    {
      log_error("Error on line %d while reading '%s'.",
        i+1, EXPECTED_OUTPUT_32);
      return EXIT_FAILURE;
    }

    assert(mt19937ar() == j);
  }

  fclose(fd);

#ifdef UINT64_C

  /* Test the 64-bit Mersenne Twister generator. */
  init_mt19937_64_by_array(init64, length);

  fd = fopen(EXPECTED_OUTPUT_64, "r");
  if (fd == NULL)
  {
    log_error("Unable to open '%s'.", EXPECTED_OUTPUT_64);
    return EXIT_FAILURE;
  }

  /* Check for the correct first 1000 output values. */
  for (int i = 0; i < 1000; i++)
  {
    if (fscanf(fd, "%"PRIu64"", &k) != 1)
    {
      log_error("Error on line %d while reading '%s'.\n",
        i+1, EXPECTED_OUTPUT_64);
      return EXIT_FAILURE;
    }

    assert(mt19937_64() == k);
  }

  fclose(fd);

#endif /* ifdef UINT64_C */

  return EXIT_SUCCESS;
}
