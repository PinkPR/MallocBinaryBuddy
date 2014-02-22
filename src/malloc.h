/**
**  Pierre-Olivier "PinkPR" DI GIUSEPPE
**  February 2014
*/

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>

# include "utils.h"

typedef struct header
{
  size_t          size;
  struct header*  next;
  struct header*  prev;
} header;

# define PAGE_SIZE      4096
# define PAGE_SIZE_POW  13
# define HEADER_SIZE    (sizeof (struct header))
# define MIN_SIZE       (getnextpow2(HEADER_SIZE))
# define MAX_SIZE       (PAGE_SIZE - HEADER_SIZE)
# define PROT           (PROT_READ | PROT_WRITE)
# define FLAGS          (MAP_ANON | MAP_PRIVATE)

header* free_blocks[PAGE_SIZE_POW + 1];

void* malloc(size_t size);

#endif /* MALLOC_H */
