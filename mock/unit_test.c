#include "unit.h"
#include <cutest/CuTest.h>
#include <stdio.h>

#ifndef NULL
#define NULL (void *)0
#endif

/*
static void unit_setup()
{
  region * r;
  while ((r = r_begin())!=0) {
    unit * u;
    while ((u=r->units)!=0) {
      u_destroy(u);
    }
    r_destroy(r);
  }
}
*/
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

int main(int argc, char** argv)
{
  CuString *output = CuStringNew();
  CuSuite *suite = CuSuiteNew();

  SUITE_ADD_TEST(suite, test_unit_create);
  SUITE_ADD_TEST(suite, test_unit_create_no_id_reuse);

  CuSuiteRun(suite);
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);
  printf("%s %s\n", argv[0], output->buffer);
  return suite->failCount;
}
