#include "cursor.h"
#include "game.h"
#include "region.h"
#include "unit.h"
#include "../platform.h"
#include <cutest/CuTest.h>
#include <errno.h>

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

static void test_add_event_does_not_crash(CuTest * tc)
{
  svc.add_event("test", 42);
  CuAssertIntEquals(tc, 0, errno);
}

static void test_region_iteration(CuTest * tc)
{
  struct region * results[4];
  void * cur;
  icursor * icur;
  int i, n = 0;

  svc.reset();

  for (i=0;i!=3;++i) {
    svc.regions->create(0, i);
  }
  cur = svc.get_regions(&icur);
  CuAssertPtrNotNull(tc, cur);
  CuAssertPtrNotNull(tc, icur);
  CuAssertIntEquals(tc, 3, icur->get(cur, 4, (void**)results));
  for (i=0;i!=3;++i) {
    int x, y;
    svc.regions->get_xy(results[i], &x, &y);
    CuAssertIntEquals(tc, 0, x);
    n |= (1<<y);
  }
  CuAssertIntEquals(tc, 7, n);

  CuAssertIntEquals(tc, 3, icur->advance(&cur, 4));
  if (icur->destroy) icur->destroy(cur);
}

void add_game_tests(CuSuite *suite)
{
  SUITE_ADD_TEST(suite, test_game_reset);
  SUITE_ADD_TEST(suite, test_region_iteration);
  SUITE_ADD_TEST(suite, test_add_event_does_not_crash);
}

