#include <svc/game.h>
#include <svc/unit.h>
#include <svc/region.h>
#include <svc/cursor.h>

#include "unit.h"
#include "keyvalue.h"
#include "region.h"

static void reset_game(void) {
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

struct iunit units = {
  &u_create,
  &u_destroy,
  &unit_get_uid,
  &unit_get_region,
  &unit_set_region,
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

static int ruc_get(void * cursor, int n, void * results[]) {
  unit * u = (unit *)cursor;
  int i = 0;
  for (i=0;u && n;++i,--n) {
    results[i] = (void *)u;
    u = u->next;
  }
  return i;
}

static int ruc_advance(void ** cursor, int n) {
  int i = 0;
  for (i=0;*cursor && n;++i,--n) {
    unit * u = (*cursor);
    cursor = (void **)&u->next;
  }
  return i;
}

struct icursor region_unit_cursor = {
  0,
  &ruc_get,
  &ruc_advance
};

static void * region_get_units(const region * r, icursor ** ic) {
  *ic = &region_unit_cursor;
  return r->units;
}

struct iregion regions = {
  &r_create,
  &r_destroy,
  &region_get_xy,
  &region_get_adj,
  &region_get_units
};

struct igame svc = {
  &units, &regions, &reset_game
};
