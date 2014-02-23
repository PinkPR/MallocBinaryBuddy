/**
**  Pierre-Olivier "PinkPR" DI GIUSEPPE
**  February 2014
*/

#include "utils.h"
#include "malloc.h"

static void delete_block(header* block)
{
  if (block->prev)
    block->prev->next = block->next;

  if (block->next)
    block->next->prev = block->prev;
  else
    free_blocks[block->size] = block->next;
}

static int recompose(header* block)
{
  header* buddy = (char*) (((uintptr_t) block) ^ mypow(2, block->size));

  if (buddy->free && buddy->size == block->size)
  {
    block->size++;
    delete_block(buddy);
    add_block(block, block->size);

    return 1;
  }

  return 0;
}

static void free_page(header* block)
{
  munmap(block, (block->size - PAGE_SIZE_POW + 1) * PAGE_SIZE);
}

void free(void* block)
{
  header* blockk = (char*) block - HEADER_SIZE;
  blockk->free = 1;

  if (blockk->size >= PAGE_SIZE_POW)
  {
    free_page(blockk);
    return;
  }

  while (recompose(blockk))
  {
    if (blockk->size == PAGE_SIZE_POW)
      free_page(blockk);
  }
}
