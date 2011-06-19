#include "../platform.h"
#include "unit.h"
#include <cutest/CuTest.h>

static void test_unit_create(CuTest * tc)
{
  unit * u = u_create();
  unit * u2 = u_create();
  
  CuAssertPtrNotNull(tc, u);
  CuAssertPtrEquals(tc, 0, u->next);
  CuAssertPtrEquals(tc, 0, u->stats);

  CuAssertTrue(tc, 0!=u->uid);
  CuAssertTrue(tc, u!=u2);
  CuAssertTrue(tc, u->uid!=u2->uid);
}

static void test_unit_create_no_id_reuse(CuTest * tc)
{
  unit * u;
  int uid;

  u = u_create();
  uid = u->uid;
  u_destroy(u);
  u = u_create();
  CuAssertTrue(tc, u->uid!=uid);
}

static void test_unit_get(CuTest * tc)
{
  unit * u;
  int uid;

  u = u_create();
  uid = u->uid;
  CuAssertPtrEquals(tc, u, u_get(uid));
}

void add_unit_tests(CuSuite *suite)
{
  SUITE_ADD_TEST(suite, test_unit_create);
  SUITE_ADD_TEST(suite, test_unit_create_no_id_reuse);
  SUITE_ADD_TEST(suite, test_unit_get);
}
