#include "region.h"
#include <stdlib.h>

static region * regions;

region * r_create(int x, int y)
{
  region * r = regions;
  while (r) {
    if (r->x==x && r->y==y) return r;
    r = r->next;
  }
  r = malloc(sizeof(region));
  r->x = x;
  r->y = y;
  r->stats = 0;
  r->next = regions;
  regions = r;
  return r;
}
