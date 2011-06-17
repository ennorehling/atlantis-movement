#include "region.h"
#include <stdlib.h>

static region * regions;

region * r_begin(void)
{
  return regions;
}

region * r_get(int x, int y)
{
  region * r;
  for (r=regions;r;r=r->next) {
    if (r->x==x && r->y==y) return r;
  }
  return 0;
}

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

void r_destroy(region * r)
{
  region ** rp = &regions;
  while (*rp!=r) {
    rp = &(*rp)->next;
  }
  *rp = r->next;
  free(r);
}
