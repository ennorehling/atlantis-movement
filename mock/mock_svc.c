#include <svc/game.h>
#include <svc/unit.h>
#include <svc/region.h>
#include <svc/cursor.h>

#include "unit.h"
#include "keyvalue.h"
#include "region.h"

#include <stdlib.h>

static void reset_game(void) {
  u_free_all();
  r_free_all();
}

static int unit_get_uid(const unit * u) {
  return u->uid;
}

static region * unit_get_region(const unit * u) {
  return (region *)kv_get(u->stats, "region");
}

static void unit_set_region(unit * u, region * r) {
  kv_set(&u->stats, "region", r);
}

static int unit_get_movement_speed(const unit * u) {
  return kv_geti(u->stats, "speed");
}

struct iunit units = {
  &u_create,
  &u_destroy,
  &u_get,
  &unit_get_uid,
  &unit_get_region,
  &unit_set_region,
  &u_get_moves,
  &unit_get_movement_speed,
};

static void region_get_xy(const region * r, int *x, int * y) {
  *x = r->x;
  *y = r->y;
}

static void region_get_adj(const region * r, region * result[]) {
  result[0] = r_get(r->x-1, r->y-1);
  result[1] = r_get(r->x, r->y-1);

  result[2] = r_get(r->x-1, r->y);
  result[3] = r_get(r->x+1, r->y);

  result[4] = r_get(r->x, r->y+1);
  result[5] = r_get(r->x+1, r->y+1);
}

static int luc_get(void * cursor, int n, void * results[]) {
  unit * u = (unit *)cursor;
  int i = 0;
  for (i=0;u && n;++i,--n) {
    results[i] = (void *)u;
    u = u->next;
  }
  return i;
}

static int luc_advance(void ** cursor, int n) {
  int i = 0;
  unit * u = (unit *)*cursor;
  for (i=0;u && n;++i,--n) {
    u = u->next;
  }
  *cursor = (void *)u;
  return i;
}

struct icursor linked_unit_cursor = {
  0,
  &luc_get,
  &luc_advance
};

static void * region_get_units(const region * r, icursor ** ic) {
  *ic = &linked_unit_cursor;
  return r->units;
}

static int lrc_get(void * cursor, int n, void * results[]) {
  region * r = (region *)cursor;
  int i = 0;
  for (i=0;r && n;++i,--n) {
    results[i] = (void *)r;
    r = r->next;
  }
  return i;
}

static int lrc_advance(void ** cursor, int n) {
  int i = 0;
  region * r = (region *)*cursor;
  for (i=0;r && n;++i,--n) {
    r = r->next;
  }
  *cursor = (void *)r;
  return i;
}

struct icursor linked_region_cursor = {
  0,
  &lrc_get,
  &lrc_advance
};

int region_get_movement_cost(const region * from, const region * to)
{
  region * adj[MAXDIRECTIONS];
  int i;
  region_get_adj(from, adj);
  for (i=0;i!=MAXDIRECTIONS;++i) {
    if (adj[i]==to) {
      return 1;
    }
  }
  return -1;
}

struct iregion regions = {
  &r_create,
  &r_destroy,
  &r_get,
  &region_get_xy,
  &region_get_adj,
  &region_get_units,
  &r_add_unit,
  &r_remove_unit,
  &region_get_movement_cost
};

void * game_get_regions(icursor ** ic) {
  *ic = &linked_region_cursor;
  return (void *)r_begin();
}

static void add_event(const char * event, ...)
{
  
}

struct igame svc = {
  &units,
  &regions,
  MAXDIRECTIONS,
  
  &reset_game,
  &game_get_regions,
  &add_event,
};
