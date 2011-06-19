#include "game.h"
#include "region.h"
#include "cursor.h"

#include <cutest/CuTest.h>
#include <stdio.h>

#ifndef NULL
#define NULL (void *)0
#endif

static void test_region_create(CuTest * tc)
{
  struct region * r;
  void * cur;
  struct icursor * icur;
  int x, y;

  test_interface(tc);
  svc.reset();

  r = svc.regions->create(4, 2);

  CuAssertPtrNotNull(tc, r);
  svc.regions->get_xy(r, &x, &y);
  CuAssertIntEquals(tc, 4, x);
  CuAssertIntEquals(tc, 2, y);
  
  cur = svc.regions->get_units(r, &icur);
  CuAssertIntEquals(tc, 0, icur->get(cur, 1, 0));
}

static void test_region_create_twice(CuTest * tc)
{
  struct region * r1, * r2;

  test_interface(tc);
  svc.reset();

  r1 = svc.regions->create(0, 0);
  r2 = svc.regions->create(0, 0);
  CuAssertPtrEquals(tc, r1, r2);
}

void add_region_tests(CuSuite *suite)
{
  SUITE_ADD_TEST(suite, test_region_create);
  SUITE_ADD_TEST(suite, test_region_create_twice);
}
