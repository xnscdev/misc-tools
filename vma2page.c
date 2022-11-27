/* Copyright (c) XNSC 2022
   This code is licensed under the MIT license (see LICENSE for details)

   Calculates offsets in all AMD64 page table structures given a 
   64-bit virtual memory address. */

#include <stdio.h>

unsigned long addr;

static unsigned long
bits_range (unsigned int start, unsigned int end)
{
  return (addr >> start) & ((1 << (end - start)) - 1);
}

int
main (void)
{
  unsigned long bits;
  printf ("Enter address: 0x");
  fflush (stdout);
  scanf ("%lx", &addr);
  bits = bits_range (48, 64);
  printf ("Sign extend:  %#-8lx %ld\n", bits, bits);
  bits = bits_range (39, 48);
  printf ("PML4T offset: %#-8lx %ld\n", bits, bits);
  bits = bits_range (30, 39);
  printf ("PDPT offset:  %#-8lx %ld\n", bits, bits);
  bits = bits_range (21, 30);
  printf ("PDT offset:  %#-8lx %ld\n", bits, bits);
  bits = bits_range (12, 21);
  printf ("PT offset: %#-8lx %ld\n", bits, bits);
  bits = bits_range (0, 12);
  printf ("Page offset: %#-8lx %ld\n", bits, bits);
  return 0;
}
