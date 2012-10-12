/* Copyright (C) 2012 C G Wrench. All rights reserved.
 * This file is part of librandom and is released under the BSD 2-Clause
 * License. See the file COPYING for the full license text.
 */

/* Unit tests for the Mersenne Twistert pseudo-random number generator. */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <inttypes.h>

#include "../mt19937ar.h"

#undef NDEBUG

/* File containing expected output for the first 1000 calls to mt19937ar(). */
const char EXPECTED_OUTPUT[] = "unit_test_mt19937ar.out";

int main(void)
{
  FILE *fd;
  uint32_t init[4]={0x123, 0x234, 0x345, 0x456};
  int length=4;
  uint32_t j;

  init_mt19937ar_by_array(init, length);

  fd = fopen(EXPECTED_OUTPUT, "r");
  if (fd == NULL)
  {
    fprintf(stderr,"Error:: Unable to open '%s'.\n", EXPECTED_OUTPUT);
    return EXIT_FAILURE;
  }

  /* Check for the correct first 1000 output values. */
  for (int i=0; i < 1000; i++)
  {
    if (fscanf(fd, "%"PRIu32"", &j) != 1)
    {
      fprintf(stderr,"Error:: Error on line %d while reading '%s'.\n",
        i+1, EXPECTED_OUTPUT);
      return EXIT_FAILURE;
    }
    assert(mt19937ar() == j);
  }

  fclose(fd);

  return EXIT_SUCCESS;
}
