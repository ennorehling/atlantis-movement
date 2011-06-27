#include "region.h"
#include "unit.h"
#include "keyvalue.h"
#include <stdlib.h>
#include <assert.h>

static region * regions;

void r_free_all(void)
{
  region * r;
  while ((r = regions)!=0) {
    r_destroy(r);
  }
}

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
  r->units = 0;
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

void r_add_unit(struct region * r, struct unit * u)
{
  unit ** up = &r->units;
  assert(u->next==0);
  while (*up) {
    up = &(*up)->next;
  }
  *up = u;
  kv_set(&u->stats, "region", r);
}

void r_remove_unit(struct region * r, struct unit * u)
{
  unit ** up = &r->units;
  assert(kv_get(u->stats, "region")==r);
  while (*up!=u) {
    up = &(*up)->next;
  }
  *up = u->next;
  u->next = 0;
  kv_set(&u->stats, "region", 0);
}
