/* Copyright (c) XNSC 2022
   This code is licensed under the MIT license (see LICENSE for details)

   Calculates a 64-bit virtual memory address given offsets for all
   page table structures for AMD64. */

#include <stdio.h>

static unsigned long
prompt (const char *input)
{
  unsigned long result;
  printf ("%s", input);
  fflush (stdout);
  scanf ("%lu", &result);
  return result;
}

int
main (void)
{
  unsigned long addr = 0;
  unsigned long pml4e = prompt ("PML4T offset: ");
  if (pml4e & 0x100)
    addr = 0xffffUL << 48;
  addr |= pml4e << 39;
  addr |= prompt ("PDPT offset: ") << 30;
  addr |= prompt ("PDT offset: ") << 21;
  addr |= prompt ("PT offset: ") << 12;
  addr |= prompt ("Page offset: ");
  printf ("%#lx\n", addr);
  return 0;
}
