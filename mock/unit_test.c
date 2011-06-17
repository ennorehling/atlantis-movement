#include "unit.h"
#include <cutest/CuTest.h>
#include <stdio.h>

#ifndef NULL
#define NULL (void *)0
#endif

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

int main(int argc, char** argv)
{
  CuString *output = CuStringNew();
  CuSuite *suite = CuSuiteNew();

  SUITE_ADD_TEST(suite, test_unit_create);
  
  CuSuiteRun(suite);
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);
  printf("%s\n", output->buffer);
  return suite->failCount;
}
