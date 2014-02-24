/**
**  Pierre-Olivier "PinkPR" DI GIUSEPPE
**  February 2014
*/

#include "malloc.h"

void* calloc(size_t size, size_t nb)
{
  void* ptr = malloc(size * nb);

  if (ptr)
  {
    size_t ssize = mypow(2, (((header*) ((char*) ptr - 8))->size)) - 8;
    ssize /= 8;

    for (size_t i; i < ssize; i++)
      ((size_t*) ptr)[i] = 0;
  }

  return ptr;
}
