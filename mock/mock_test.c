#include <cutest/CuTest.h>
#include <stdio.h>

extern void add_keyvalue_tests(CuSuite * suite);
extern void add_region_tests(CuSuite * suite);
extern void add_unit_tests(CuSuite * suite);

int main(int argc, char** argv)
{
  CuString *output = CuStringNew();
  CuSuite *suite = CuSuiteNew();

  add_keyvalue_tests(suite);
  add_region_tests(suite);
  add_unit_tests(suite);

  CuSuiteRun(suite);
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);
  printf("%s %s\n", argv[0], output->buffer);
  return suite->failCount;
}
