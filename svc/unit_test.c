#include "game.h"
#include "unit.h"
#include <cutest/CuTest.h>
#include <stdio.h>

#ifndef NULL
#define NULL (void *)0
#endif

static void test_interface(CuTest * tc)
{
  CuAssertPtrNotNull(tc, svc.reset);
  CuAssertPtrNotNull(tc, svc.units);
  CuAssertPtrNotNull(tc, svc.units->create);
  CuAssertPtrNotNull(tc, svc.units->get_uid);
  CuAssertPtrNotNull(tc, svc.units->get_region);
}

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

void add_unit_tests(CuSuite *suite)
{
  SUITE_ADD_TEST(suite, test_unit_create);
  SUITE_ADD_TEST(suite, test_unit_create_no_id_reuse);
}
