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
  size_t          free:1;
  size_t          size:63;
  struct header*  next;
  struct header*  prev;
} header;

# define PAGE_SIZE      4096
# define PAGE_SIZE_POW  12
# define HEADER_SIZE    8
# define HD_SIZE        (sizeof (struct header))
# define PROT           (PROT_READ | PROT_WRITE | PROT_EXEC)
# define FLAGS          (MAP_ANON | MAP_PRIVATE)

header* free_blocks[PAGE_SIZE_POW + 1];

void  add_block(header* block, size_t size);
void* malloc(size_t size);
void  free(void* block);
void* realloc(void* ptr, size_t size);
void* calloc(size_t size, size_t nb);

#endif /* MALLOC_H */
