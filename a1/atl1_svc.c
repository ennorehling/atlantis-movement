#include "atlantis1.h"
#include <svc/game.h>
#include <svc/unit.h>
#include <svc/region.h>
#include <svc/cursor.h>
#include <stdlib.h>
#include <limits.h>

static region * limbo; /* where units go that are not in the world */

static unit * u_create(void) {
  unit * u = createunit(limbo);
  return u;
}

static region * u_get_region(const unit * u)
{
  region * r;
  for (r=regions;r;r=r->next) {
    unit *u2;
    for (u2=r->units;u2;u2=u2->next) {
      if (u2==u) {
        return r==limbo?0:r;
      }
    }
  }
  return 0;
}

static unit * u_get(int uid) {
  region * r;
  for (r=regions;r;r=r->next) {
    unit * u;
    for (u=r->units;u;u=u->next) {
      if (u->no==uid) return u;
    }
  }
  return 0;
}

static int u_get_uid(const unit * u)
{
  return u->no;
}

static void u_set_region(unit *u, region *r)
{
  region * rx = u_get_region(u);
  moveunit(u, rx?rx:limbo, r?r:limbo);
}

static void u_destroy(unit * u)
{
  region * r = u_get_region(u);
  destroyunit(u, r?r:limbo);
}

static int u_get_moves(const unit * u, region *result[], int offset, int n)
{
  return 0;
}

static int u_get_speed(const unit * u)
{
  return 1;
}

struct iunit svc_units = {
  &u_create,
  &u_destroy,
  &u_get,
  &u_get_uid,
  &u_get_region,
  &u_set_region,
  &u_get_moves,
  &u_get_speed,
};

void r_destroy(region *r)
{
}

void r_get_xy(const region *r, int *x, int *y)
{
  *x = r->x;
  *y = r->y;
}

static int get_next_units(void * cursor, int n, void * results[])
{
  unit * u = (unit *)cursor;
  int i = 0;
  while (u && i!=n) {
    u = u->next;
  }
  return i;
}

static int advance_next_units(void ** cursor, int n)
{
  unit ** up = (unit **)cursor;
  int i = 0;
  while (*up && i++!=n) {
    up = &(*up)->next;
  }
  return i;
}

static struct icursor region_unit_cursor = {
  0, &get_next_units, &advance_next_units
};

void * r_get_units(const region * r, icursor ** icur)
{
  *icur = &region_unit_cursor;
  return r->units;
}

void r_get_adj(const region *r, region * result[])
{
  int i;
  for (i=0;i!=4;++i) {
    result[i] = r->connect[i];
  }
}

void r_add_unit(region * r, unit * u)
{
  region * rx = u_get_region(u);
  moveunit(u, rx?rx:limbo, r);
}

void r_remove_unit(region *r, unit *u)
{
  moveunit(u, r, limbo);
}

int r_get_movement_cost(const region *r, const region *r2)
{
  return 1;
}

struct iregion svc_regions = {
  &createregion,
  &r_destroy,
  &findregion,
  &r_get_xy,
  &r_get_adj,
  &r_get_units,
  &r_add_unit,
  &r_remove_unit,
  &r_get_movement_cost
};


static void game_reset(void)
{
  regions = 0;
  limbo = createregion(INT_MAX, INT_MAX);
}

static int get_next_regions(void * cursor, int n, void * results[])
{
  region * r = (region *)cursor;
  int i = 0;
  while (r && i!=n) {
    if (r!=limbo) {
      results[i++] = r;
    }
    r = r->next;
  }
  return i;
}

static int advance_next_regions(void ** cursor, int n)
{
  region ** rp = (region **)cursor;
  int i = 0;
  while (*rp && i++!=n) {
    if (*rp == limbo) --i;
    rp = &(*rp)->next;
  }
  return i;
}

static struct icursor region_cursor = {
  0, &get_next_regions, &advance_next_regions
};

static void * game_get_regions(icursor ** icur)
{
  *icur = &region_cursor;
  return regions;
}

struct igame svc = {
  &svc_units,
  &svc_regions,
  4,
  
  &game_reset,
  &game_get_regions,
};
