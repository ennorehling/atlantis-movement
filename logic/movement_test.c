#include <cutest/CuTest.h>
#include <stdio.h>

#include <svc/game.h>
#include <svc/unit.h>
#include <svc/region.h>

#include "../platform.h"
#include "logic.h"

static void test_movement(CuTest * tc) {
  struct unit * u;
  struct region * r;
  
  svc.reset();
  r = svc.regions->create(0, 0);
  u = svc.units->create();
  svc.units->set_region(u, r);
  do_movement();
  CuAssertPtrEquals(tc, r, svc.units->get_region(u));
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
