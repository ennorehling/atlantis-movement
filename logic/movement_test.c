#include <cutest/CuTest.h>
#include <stdio.h>
#include <stdlib.h>

#include <svc/game.h>
#include <svc/unit.h>
#include <svc/region.h>

#include <mock/unit.h>
#include <mock/region.h>
#include <mock/keyvalue.h>

#include "../platform.h"
#include "logic.h"

static void test_no_movement(CuTest * tc) {
  struct unit * u;
  struct region * r;
  
  svc.reset();
  r = svc.regions->create(0, 0);
  u = svc.units->create();
  svc.units->set_region(u, r);
  do_movement();
  CuAssertPtrEquals(tc, r, svc.units->get_region(u));
}

static void test_easy_path(CuTest * tc) {
  unit * u;
  region * r, ** path;

  svc.reset();

  r = svc.regions->create(0, 0);
  u = svc.units->create();
  svc.regions->add_unit(r, u);
  kv_seti(&u->stats, "speed", 1);

  path = malloc(sizeof(region *)*2);
  path[0] = svc.regions->create(1, 0);
  path[1] = 0;
  u_set_moves(u, path);

  svc.units->set_region(u, r);
  do_movement();
  CuAssertPtrEquals(tc, path[0], svc.units->get_region(u));
}

static void test_move_too_far(CuTest * tc) {
  unit * u;
  region * r, ** path;

  svc.reset();

  r = svc.regions->create(0, 0);
  u = svc.units->create();
  svc.regions->add_unit(r, u);
  kv_seti(&u->stats, "speed", 1);

  path = malloc(sizeof(region *)*3);
  path[0] = svc.regions->create(1, 0);
  path[1] = svc.regions->create(2, 0);
  path[2] = 0;
  u_set_moves(u, path);

  svc.units->set_region(u, r);
  do_movement();
  CuAssertPtrEquals(tc, path[0], svc.units->get_region(u));
}

#define MAXEVENTS 32
static const char * events[MAXEVENTS];
static int num_events;
static void record_events(const char * event, ...) {
  if (num_events<MAXEVENTS) {
    events[num_events++] = event;
  }
}

static void test_move_illegal(CuTest * tc) {
  void (*event_cb)(const char *, ...);
  unit * u;
  region * r, ** path;

  svc.reset();

  event_cb = svc.add_event;
  svc.add_event = record_events;
  num_events = 0;

  r = svc.regions->create(0, 0);
  u = svc.units->create();
  svc.regions->add_unit(r, u);
  kv_seti(&u->stats, "speed", 1);

  path = malloc(sizeof(region *)*2);
  path[0] = svc.regions->create(2, 0);
  path[1] = 0;
  u_set_moves(u, path);

  svc.units->set_region(u, r);
  do_movement();
  CuAssertPtrEquals(tc, r, svc.units->get_region(u));

  CuAssertIntEquals(tc, 1, num_events);
  CuAssertStrEquals(tc, "illegal_move", events[0]);
  svc.add_event = event_cb;
}

int main(int argc, char** argv)
{
  CuString *output = CuStringNew();
  CuSuite *suite = CuSuiteNew();

  SUITE_ADD_TEST(suite, test_no_movement);
  SUITE_ADD_TEST(suite, test_easy_path);
  SUITE_ADD_TEST(suite, test_move_too_far);
  SUITE_ADD_TEST(suite, test_move_illegal); 

  CuSuiteRun(suite);
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);
  printf("%s %s\n", argv[0], output->buffer);
  return suite->failCount;
}
