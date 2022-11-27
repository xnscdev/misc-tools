/* Copyright (c) XNSC 2022
   This code is licensed under the MIT license (see LICENSE for details)

   Bit shift calculator CLI. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main (int argc, char **argv)
{
  unsigned long a;
  unsigned long b;
  unsigned long result;
  if (argc != 4)
    {
      fprintf (stderr, "Usage: bit-shift <x> <DIRECTION> <y>\n");
      exit (1);
    }

  a = atoi (argv[1]);
  b = atoi (argv[3]);

  if (strcasecmp (argv[2], "left") == 0)
    result = a << b;
  else if (strcasecmp (argv[2], "right") == 0)
    result = a >> b;
  else
    {
      fprintf (stderr, "Shift direction must be 'left' or 'right'\n");
      exit (1);
    }
  printf ("Result: %#lx (%lu)\n", result, result);
  return 0;
}
