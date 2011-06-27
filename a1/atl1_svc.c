#include "atlantis1.h"
#include <svc/game.h>
#include <svc/unit.h>
#include <svc/region.h>
#include <svc/cursor.h>
#include <stdlib.h>


static unit * u_create(void) {
  unit * u = createunit(0);
  return u;
}

static region * u_get_region(const unit * u)
{
  region * r;
  for (r=regions;r;r=r->next) {
    unit *u2;
    for (u2=r->units;u2;u2=u2->next) {
      if (u2==u) return r;
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
  moveunit(u, u_get_region(u), r);
}

static void u_destroy(unit * u)
{
  region * r = u_get_region(u);
  destroyunit(u, r);
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

void * r_get_units(const region * r, icursor ** icur)
{
  return 0;
}

void r_get_adj(const region *r, region * result[])
{
  
}

void r_add_unit(region * r, unit * u)
{
  region * rx = u_get_region(u);
  moveunit(u, rx, r);
}

void r_remove_unit(region *r, unit *u)
{
  moveunit(u, r, 0);
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
}

static int get_next_regions(void * cursor, int n, void * results[])
{
  return 0;
}

static int advance_next_regions(void ** cursor, int n)
{
  return 0;
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
