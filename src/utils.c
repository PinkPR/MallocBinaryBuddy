/**
**  Pierre-Olivier "PinkPR" DI GIUSEPPE
**  February 2014
*/

#include "utils.h"

size_t mypow(size_t x, size_t n)
{
  if (!n)
    return 1;
  else
    return x * mypow(x, n - 1);
}

size_t getnextpow2(size_t x)
{
  if (x == 1 || x == 0)
    return 2;

  if (x % 2)
    x--;

  x |= x >> 1;
  x |= x >> 2;
  x |= x >> 4;
  x |= x >> 8;
  x |= x >> 16;
  x |= x >> 32;
  x++;

  return x;
}

size_t getlog2(size_t x)
{
  size_t n = -1;

  for (; x; n++, x = x >> 1);

  return n;
}
