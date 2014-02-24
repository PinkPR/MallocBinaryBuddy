/**
**  Pierre-Olivier "PinkPR" DI GIUSEPPE
**  February 2014
*/

#include "malloc.h"

static void mem_copy(size_t* newptr, size_t* ptr, size_t size)
{
  size /= 8;

  for (size_t i = 0; i < size; i++)
    newptr[i] = ptr[i];
}

void* realloc(void* ptr, size_t size)
{
  header* block = (header*) ((char*) ptr - HEADER_SIZE);
  size += HEADER_SIZE;
  size_t wanted = getlog2(getnextpow2(wanted));

  if (wanted == block->size)
    return ptr;

  size_t* newptr = malloc(size);
  mem_copy(newptr, ptr, size - HEADER_SIZE);
  free(block);

  return newptr;
}
