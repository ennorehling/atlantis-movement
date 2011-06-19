#include "game.h"
#include "region.h"
#include "cursor.h"
#include "../platform.h"

#include <cutest/CuTest.h>
#include <stdio.h>

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
  if (icur->destroy) icur->destroy(cur);
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

static void test_region_add_units(CuTest * tc)
{
  struct region * r;
  struct unit * u1, * buffer[4];
  void * cur;
  struct icursor * icur;

  test_interface(tc);
  svc.reset();

  r = svc.regions->create(0, 0);

  cur = svc.regions->get_units(r, &icur);
  CuAssertIntEquals(tc, 0, icur->get(cur, 4, (void**)buffer));
  if (icur->destroy) icur->destroy(cur);

  u1 = svc.units->create();
  svc.regions->add_unit(r, u1);
  CuAssertPtrEquals(tc, r, svc.units->get_region(u1));

  cur = svc.regions->get_units(r, &icur);
  CuAssertIntEquals(tc, 1, icur->get(cur, 4, (void**)buffer));
  CuAssertPtrEquals(tc, u1, buffer[0]);
  if (icur->destroy) icur->destroy(cur);
}

static void test_region_add_units_in_order(CuTest * tc)
{
  struct region * r;
  struct unit * u1, * u2, * buffer[4];
  void * cur;
  struct icursor * icur;

  test_interface(tc);
  svc.reset();

  r = svc.regions->create(0, 0);
  u1 = svc.units->create();
  u2 = svc.units->create();
  svc.regions->add_unit(r, u1);
  svc.regions->add_unit(r, u2);

  cur = svc.regions->get_units(r, &icur);
  CuAssertIntEquals(tc, 2, icur->get(cur, 4, (void**)buffer));
  CuAssertPtrEquals(tc, u1, buffer[0]);
  CuAssertPtrEquals(tc, u2, buffer[1]);
  if (icur->destroy) icur->destroy(cur);
}

static void test_region_iterate_units(CuTest * tc)
{
  struct region * r;
  struct unit * u1, * u2, * buffer[4];
  void * cur;
  struct icursor * icur;

  test_interface(tc);
  svc.reset();

  r = svc.regions->create(0, 0);
  u1 = svc.units->create();
  u2 = svc.units->create();
  svc.regions->add_unit(r, u1);
  svc.regions->add_unit(r, u2);

  cur = svc.regions->get_units(r, &icur);
  CuAssertIntEquals(tc, 1, icur->advance(&cur, 1));
  CuAssertIntEquals(tc, 1, icur->get(cur, 4, (void**)buffer));
  CuAssertPtrEquals(tc, u2, buffer[0]);
  CuAssertIntEquals(tc, 1, icur->advance(&cur, 2));
  if (icur->destroy) icur->destroy(cur);
}

static void test_region_remove_units(CuTest * tc)
{
  struct region * r;
  struct unit * u1, * u2, * buffer[4];
  void * cur;
  struct icursor * icur;

  test_interface(tc);
  svc.reset();

  r = svc.regions->create(0, 0);
  u1 = svc.units->create();
  u2 = svc.units->create();
  svc.regions->add_unit(r, u1);
  svc.regions->add_unit(r, u2);

  svc.regions->remove_unit(r, u1);
  CuAssertPtrEquals(tc, 0, svc.units->get_region(u1));

  cur = svc.regions->get_units(r, &icur);
  CuAssertIntEquals(tc, 1, icur->get(cur, 4, (void**)buffer));
  CuAssertPtrEquals(tc, u2, buffer[0]);
  if (icur->destroy) icur->destroy(cur);
}

void add_region_tests(CuSuite *suite)
{
  SUITE_ADD_TEST(suite, test_region_create);
  SUITE_ADD_TEST(suite, test_region_create_twice);
  SUITE_ADD_TEST(suite, test_region_add_units);
  SUITE_ADD_TEST(suite, test_region_add_units_in_order);
  SUITE_ADD_TEST(suite, test_region_iterate_units);
  SUITE_ADD_TEST(suite, test_region_remove_units);
}
