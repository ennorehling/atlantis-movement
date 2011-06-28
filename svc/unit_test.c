#include "game.h"
#include "unit.h"
#include <cutest/CuTest.h>
#include <stdio.h>

static void test_unit_create(CuTest * tc)
{
  struct unit * u;

  test_interface(tc);
  svc.reset();

  u = svc.units->create();
  
  CuAssertPtrNotNull(tc, u);
  CuAssertPtrEquals(tc, 0, svc.units->get_region(u));
  CuAssertTrue(tc, 0!=svc.units->get_uid(u));

}

static void test_unit_get_movement_speed(CuTest * tc)
{
  struct unit * u;

  test_interface(tc);
  svc.reset();

  u = svc.units->create();
  CuAssertTrue(tc, svc.units->get_movement_speed(u)>=0);
}

static void test_unit_get_moves(CuTest * tc)
{
  struct unit * u;

  test_interface(tc);
  svc.reset();

  u = svc.units->create();
  CuAssertIntEquals(tc, 0, svc.units->get_moves(u, 0, 0, 0));
}
/*
static void test_unit_create_no_id_reuse(CuTest * tc)
{
  struct unit * u;
  int uid;

  test_interface(tc);
  svc.reset();

  u = svc.units->create();
  uid = svc.units->get_uid(u);
  svc.units->destroy(u);
  u = svc.units->create();
  CuAssertTrue(tc, svc.units->get_uid(u)!=uid);
}
 */
static void test_unit_get(CuTest * tc)
{
  struct unit * u;
  int uid;
  
  test_interface(tc);
  svc.reset();
  
  u = svc.units->create();
  uid = svc.units->get_uid(u);
  CuAssertPtrEquals(tc, u, svc.units->get(uid));
  svc.units->destroy(u);  
  CuAssertPtrEquals(tc, 0, svc.units->get(uid));
}

void add_unit_tests(CuSuite *suite)
{
  SUITE_ADD_TEST(suite, test_unit_create);
  SUITE_ADD_TEST(suite, test_unit_get);
/*  SUITE_ADD_TEST(suite, test_unit_create_no_id_reuse);*/
  SUITE_ADD_TEST(suite, test_unit_get_moves);
  SUITE_ADD_TEST(suite, test_unit_get_movement_speed);
}
