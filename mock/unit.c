#include "unit.h"
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
      units[i] = units[--num_units];
      break;
    }
  }
  free(u);
}

unit * u_get(int id)
{
  int i;
  for (i=0;i!=num_units;++i) {
    if (units[i]->uid==id) return units[i];
  }
  assert(i!=num_units);
  return 0;
}
