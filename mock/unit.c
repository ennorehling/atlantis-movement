#include "unit.h"
#include <stdlib.h>

static int max_unit = 0;

unit * u_create(void)
{
  unit * u = malloc(sizeof(unit));
  u->uid = ++max_unit;
  u->stats = 0;
  u->next = 0;
  return u;
}
