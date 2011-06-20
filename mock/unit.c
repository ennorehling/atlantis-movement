#include "unit.h"
#include "keyvalue.h"
#include <assert.h>
#include <stdlib.h>

static int max_unit = 0;

#define MAXUNITS 64
static unit * units[MAXUNITS];
static int num_units;

unit * u_create(void)
{
  unit * u = malloc(sizeof(unit));
  u->uid = ++max_unit;
  u->stats = 0;
  u->next = 0;
  assert(num_units<MAXUNITS);
  units[num_units++] = u;
  return u;
}

void u_destroy(unit * u)
{
  int i;
  for (i=0;i!=num_units;++i) {
    if (u==units[i]) {
      units[i--] = units[--num_units];
      break;
    }
  }
  assert(i!=num_units);
  free(kv_get(u->stats, "path"));
  free(u);
}

unit * u_get(int id)
{
  int i;
  for (i=0;i!=num_units;++i) {
    if (units[i]->uid==id) return units[i];
  }
  return 0;
}

int u_get_moves(const unit * u, struct region * result[], int offset, int n) {
  int i;
  struct region ** path = (struct region **)kv_get(u->stats, "path");

  assert(offset>=0);
  assert(n>=0);
  for (i=0;i!=n && path[i+offset];++i) {
    result[i] = path[i+offset];
  }
  if (n && path[i+offset]) return -1;
  return i;
}

void u_set_moves(unit * u, struct region * path[]) {
  kv_set(&u->stats, "path", (void *)path);
}
