#include <cutest/CuTest.h>
#include <stdio.h>

#include "game.h"
#include "region.h"
#include "unit.h"
#include "../platform.h"

void test_interface(CuTest * tc)
{
  CuAssertPtrNotNull(tc, svc.reset);
  CuAssertPtrNotNull(tc, svc.get_regions);
  CuAssertPtrNotNull(tc, svc.add_event);
  CuAssertTrue(tc, 0!=svc.max_directions);

  CuAssertPtrNotNull(tc, svc.regions);
  CuAssertPtrNotNull(tc, svc.regions->create);
  CuAssertPtrNotNull(tc, svc.regions->destroy);
  CuAssertPtrNotNull(tc, svc.regions->get_xy);
  CuAssertPtrNotNull(tc, svc.regions->get_units);

  CuAssertPtrNotNull(tc, svc.units);
  CuAssertPtrNotNull(tc, svc.units->create);
  CuAssertPtrNotNull(tc, svc.units->destroy);
  CuAssertPtrNotNull(tc, svc.units->get_uid);
  CuAssertPtrNotNull(tc, svc.units->get_region);
  CuAssertPtrNotNull(tc, svc.units->get);
  CuAssertPtrNotNull(tc, svc.units->get_moves);
  CuAssertPtrNotNull(tc, svc.units->get_movement_speed);
}

#include "game_test.c"
#include "region_test.c"
#include "unit_test.c"

#ifdef CUSTOM_TESTS
extern void add_custom_tests(CuSuite * suite);
#endif

void add_svc_tests(CuSuite * suite)
{
  SUITE_ADD_TEST(suite, test_interface);
  add_game_tests(suite);
  add_region_tests(suite);
  add_unit_tests(suite);
}

int main(int argc, char** argv)
{
  CuString *output = CuStringNew();
  CuSuite *suite = CuSuiteNew();

  add_svc_tests(suite);
#ifdef CUSTOM_TESTS
  add_custom_tests(suite);
#endif

  CuSuiteRun(suite);
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);
  printf("%s %s\n", argv[0], output->buffer);
  return suite->failCount;
}
