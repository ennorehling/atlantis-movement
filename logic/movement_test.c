#include <cutest/CuTest.h>
#include <stdio.h>

#include "../platform.h"
#include "logic.h"

static void test_movement(CuTest * tc) {
  do_movement();
}

int main(int argc, char** argv)
{
  CuString *output = CuStringNew();
  CuSuite *suite = CuSuiteNew();

  SUITE_ADD_TEST(suite, test_movement);

  CuSuiteRun(suite);
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);
  printf("%s %s\n", argv[0], output->buffer);
  return suite->failCount;
}
