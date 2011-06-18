#include <svc/game.h>
#include <svc/unit.h>
#include <svc/region.h>

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
struct iregion regions = {};
struct igame svc = {
  &units, &regions, &reset_game
};
