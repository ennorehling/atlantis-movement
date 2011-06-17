#include "region.h"
#include <cutest/CuTest.h>
#include <stdio.h>

#ifndef NULL
#define NULL (void *)0
#endif

static void test_region_create(CuTest * tc)
{
  region * r = r_create(1, 2);
  
  CuAssertPtrNotNull(tc, r);
  CuAssertPtrEquals(tc, 0, r->stats);

  CuAssertIntEquals(tc, 1, r->x);
  CuAssertIntEquals(tc, 2, r->y);
}

static void test_region_create_same_twice(CuTest * tc)
{
  region * r1 = r_create(1, 2);
  region * r2 = r_create(1, 2);
  CuAssertPtrEquals(tc, r1, r2);
}

int main(int argc, char** argv)
{
  CuString *output = CuStringNew();
  CuSuite *suite = CuSuiteNew();

  SUITE_ADD_TEST(suite, test_region_create);
  SUITE_ADD_TEST(suite, test_region_create_same_twice);
  
  CuSuiteRun(suite);
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);
  printf("%s %s\n", argv[0], output->buffer);
  return suite->failCount;
}
