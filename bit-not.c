/* Copyright (c) XNSC 2022
   This code is licensed under the MIT license (see LICENSE for details)

   Tool to calculate the bitwise inverse of an integer. */

#include <stdio.h>

int
main (void)
{
  unsigned long n;
  printf ("Enter number: 0x");
  fflush (stdout);
  scanf ("%lx", &n);
  printf ("Result: %#lx (%lu)\n", ~n, ~n);
  return 0;
}
