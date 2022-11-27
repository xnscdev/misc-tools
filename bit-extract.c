/* Copyright (c) XNSC 2022
   This code is licensed under the MIT license (see LICENSE for details)

   Tool to calculate the value of a region of bits in an integer. */

#include <err.h>
#include <stdio.h>

int
main (void)
{
  unsigned long x;
  unsigned int start;
  unsigned int end;
  printf ("Enter number: 0x");
  fflush (stdout);
  scanf ("%lx", &x);
  printf ("Enter start bit: ");
  fflush (stdout);
  scanf ("%u", &start);
  printf ("Enter end bit: ");
  fflush (stdout);
  scanf ("%u", &end);
  if (start > end || start > 64 || end > 64)
    errx (1, "bad start and end values");
  printf ("Result: %#lx\n", (x >> start) & ((1 << (end - start)) - 1));
  return 0;
}
