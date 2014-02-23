/**
**  Pierre-Olivier "PinkPR" DI GIUSEPPE
**  February 2014
*/

#include "malloc.h"

void* getnewpage(size_t size)
{
  if (size < PAGE_SIZE)
    size = PAGE_SIZE;
  else
    size = PAGE_SIZE * (size / PAGE_SIZE + 1);

  header* block = mmap(NULL, size, PROT, FLAGS, 0, 0);

  block->size = PAGE_SIZE_POW + size / (PAGE_SIZE + 1);

  return block;
}

void make_header(header* block, size_t size)
{
  block->next = NULL;
  block->size = size;
  block->free = 1;
  block->prev = NULL;

  free_blocks[size] = block;
}

void add_block(header* block, size_t size)
{
  if (free_blocks[size])
    free_blocks[size]->prev = block;

  block->prev = NULL;
  block->next = free_blocks[size];

  free_blocks[size] = block;
}

void split_block(size_t wanted)
{
  if (wanted == PAGE_SIZE_POW + 1)
  {
    free_blocks[PAGE_SIZE_POW] = getnewpage(PAGE_SIZE);
    make_header(free_blocks[PAGE_SIZE_POW], PAGE_SIZE_POW);
  }
  else if (!(free_blocks[wanted]))
  {
    split_block(wanted + 1);
  }
  else
  {
    header* block1 = NULL;
    header* block2 = NULL;
    block1 = free_blocks[wanted];
    block2 = ((char*) block1) + mypow(2, wanted - 1);
    free_blocks[wanted] = block1->next;

    if (free_blocks[wanted])
      free_blocks[wanted]->prev = NULL;

    block1->size = wanted - 1;
    block2->size = wanted - 1;
    block2->free = 1;

    add_block(block1, block1->size);
    add_block(block2, block2->size);
  }
}

header* get_block(size_t wanted)
{
  while (!(free_blocks[wanted]))
    split_block(wanted + 1);

  header* block = free_blocks[wanted];
  free_blocks[wanted] = block->next;

  if (free_blocks[wanted])
    free_blocks[wanted]->prev = NULL;

  block->next = NULL;
  block->free = 0;

  return block;
}

void* malloc(size_t size)
{
  size += HEADER_SIZE;

  if (size > PAGE_SIZE)
    return (char*) getnewpage(size) + HEADER_SIZE;

  return (char*) get_block(getlog2(getnextpow2(size))) + HEADER_SIZE;
}
