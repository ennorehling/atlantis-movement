#include "cursor.h"
#include "game.h"
#include "region.h"
#include "unit.h"
#include "../platform.h"
#include <cutest/CuTest.h>

static void test_game_reset(CuTest * tc) {
  struct region * r, * first;
  void * cur;
  icursor * icur;

  test_interface(tc);
  svc.reset();

  r = svc.regions->create(0, 0);
  CuAssertPtrNotNull(tc, r);
  cur = svc.get_regions(&icur);
  CuAssertPtrNotNull(tc, icur);
  CuAssertIntEquals(tc, 1, icur->get(cur, 1, (void **)&first));
  CuAssertPtrEquals(tc, r, first);
  if (icur->destroy) icur->destroy(cur);

  svc.reset();

  first = 0;
  cur = svc.get_regions(&icur);
  CuAssertPtrNotNull(tc, icur);
  CuAssertIntEquals(tc, 0, icur->get(cur, 1, (void **)&first));
  CuAssertPtrEquals(tc, 0, first);
  if (icur->destroy) icur->destroy(cur);
}

void add_game_tests(CuSuite *suite)
{
  SUITE_ADD_TEST(suite, test_game_reset);
}

