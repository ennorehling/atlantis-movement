#include "cursor.h"
#include "game.h"
#include "region.h"
#include "unit.h"
#include "../platform.h"
#include <cutest/CuTest.h>

static void test_game_reset(CuTest * tc) {
  struct region * r;
  struct unit * u;
  void *cur, *result;
  icursor *icur;
  int uid;

  test_interface(tc);
  svc.reset();

  r = svc.regions->create(0, 0);
  u = svc.units->create();
  uid = svc.units->get_uid(u);

  cur = svc.get_regions(&icur);
  CuAssertPtrNotNull(tc, icur);
  CuAssertIntEquals(tc, 1, icur->get(cur, 1, &result));
  CuAssertPtrEquals(tc, r, result);
  if (icur->destroy) icur->destroy(cur);

  CuAssertPtrEquals(tc, u, svc.units->get(uid));

  svc.reset();

  result = 0;

  cur = svc.get_regions(&icur);
  CuAssertPtrNotNull(tc, icur);
  CuAssertIntEquals(tc, 0, icur->get(cur, 1, &result));
  CuAssertPtrEquals(tc, 0, result);
  if (icur->destroy) icur->destroy(cur);

  CuAssertPtrEquals(tc, 0, svc.units->get(uid));
}

void add_game_tests(CuSuite *suite)
{
  SUITE_ADD_TEST(suite, test_game_reset);
}

