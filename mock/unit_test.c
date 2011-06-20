#include "../platform.h"
#include "unit.h"
#include <cutest/CuTest.h>
#include <stdlib.h>
#include <string.h>

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

static void test_unit_path(CuTest * tc)
{
  unit * u;
  struct region * path[5];
  struct region * result[5];
  int i;

  u = u_create();
  for (i=0;i!=4;++i) {
    path[i] = (struct region *)(path+i);
  }
  path[i] = 0;
  u_set_moves(u, path);
  memset(result, 0, sizeof(result));
  CuAssertIntEquals(tc, 0, u_get_moves(u, result, 0, 0));

  CuAssertIntEquals(tc, -1, u_get_moves(u, result, 0, 1));
  CuAssertPtrEquals(tc, (struct region *)(path+0), result[0]);
  CuAssertPtrEquals(tc, 0, result[1]);

  CuAssertIntEquals(tc, 4, u_get_moves(u, result, 0, 4));
  CuAssertIntEquals(tc, 3, u_get_moves(u, result, 1, 4));
  CuAssertPtrEquals(tc, (struct region *)(path+1), result[0]);
}

void add_unit_tests(CuSuite *suite)
{
  SUITE_ADD_TEST(suite, test_unit_create);
  SUITE_ADD_TEST(suite, test_unit_create_no_id_reuse);
  SUITE_ADD_TEST(suite, test_unit_get);
  SUITE_ADD_TEST(suite, test_unit_path);
}
