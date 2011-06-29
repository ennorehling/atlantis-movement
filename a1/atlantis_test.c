#include "atlantis.h"
#include <cutest/CuTest.h>
#include <string.h>
#include <stdio.h>

static void test_createregion(CuTest * tc)
{
    region * r;
    
    resetgame();
    r = createregion(2, 3);
    CuAssertPtrNotNull(tc, r);
    CuAssertIntEquals(tc, 2, r->x);
    CuAssertIntEquals(tc, 3, r->y);

    CuAssertPtrEquals(tc, 0, r->next);
}

static void test_createunit(CuTest * tc)
{
    region * r;
    unit *ux;
    
    resetgame();
    r = createregion(0, 0);
    ux = createunit(r);
    CuAssertPtrNotNull(tc, ux);

    CuAssertPtrEquals(tc, ux, r->units);
}

static void test_destroyunit(CuTest * tc)
{
    region *r;
    unit *u;

    resetgame();
    r = createregion(0, 0);
    u = createunit(r);
    destroyunit(u, r);
    CuAssertPtrEquals(tc, 0, r->units);    
}

static void test_createregion_once(CuTest * tc)
{
    region *r1, *r2;

    resetgame();
    r1 = createregion(0, 0);
    r2 = createregion(0, 0);
    CuAssertPtrEquals(tc, r1, r2);    
}

static void test_moveunit(CuTest * tc)
{
    region *r, *r2;
    unit *u;
    
    resetgame();
    r = createregion(0, 0);
    r2 = createregion(0, 1);
    u = createunit(r);
    moveunit(u, r, r2);

    CuAssertPtrEquals(tc, u, r2->units);
    CuAssertPtrEquals(tc, 0, r->units);
}

static void test_movement(CuTest * tc)
{
    unit * u;
    region *r1, *r2;

    resetgame();
    r1 = createregion(0, 0);
    r1->terrain = T_PLAIN;
    r2 = createregion(1, 0);
    r2->terrain = T_PLAIN;
    u = createunit(r1);
    strcpy(u->thisorder, "move east");
    process_movement();
    CuAssertPtrEquals(tc, u, r2->units);
}

static void test_sailing(CuTest * tc)
{
    ship *sh;
    unit *u;
    region *r1, *r2;

    resetgame();
    r1 = createregion(0, 0);
    r1->terrain = T_OCEAN;
    r2 = createregion(1, 0);
    r2->terrain = T_OCEAN;
    u = createunit(r1);
    sh = createship(r1, SH_LONGBOAT);
    u->ship = sh;
    u->owner = 1;
    strcpy(u->thisorder, "sail east");
    process_movement();
    CuAssertPtrEquals(tc, u, r2->units);
    CuAssertPtrEquals(tc, sh, r2->ships);
}

static void test_move_captain(CuTest * tc)
{
    ship *sh;
    unit *u;
    region *r1, *r2;

    resetgame();
    r1 = createregion(0, 0);
    r1->terrain = T_PLAIN;
    r2 = createregion(1, 0);
    r2->terrain = T_PLAIN;
    u = createunit(r1);
    sh = createship(r1, SH_LONGBOAT);
    u->ship = sh;
    u->owner = 1;
    strcpy(u->thisorder, "move east");
    process_movement();
    CuAssertPtrEquals(tc, u, r2->units);
    CuAssertPtrEquals(tc, sh, r1->ships);
}

static void test_movement_invalid_direction(CuTest * tc)
{
    unit * u;
    region *r1, *r2;

    resetgame();
    r1 = createregion(0, 0);
    r1->terrain = T_PLAIN;
    r2 = createregion(1, 0);
    r2->terrain = T_PLAIN;
    u = createunit(r1);
    strcpy(u->thisorder, "move blerg");
    process_movement();
    CuAssertPtrEquals(tc, u, r1->units);
}

static void test_movement_into_ocean(CuTest * tc)
{
    unit * u;
    region *r1, *r2;

    resetgame();
    r1 = createregion(0, 0);
    r1->terrain = T_PLAIN;
    r2 = createregion(1, 0);
    r2->terrain = T_OCEAN;
    u = createunit(r1);
    u->faction = createfaction();
    strcpy(u->thisorder, "move east");
    process_movement();
    CuAssertPtrEquals(tc, u, r1->units);
    sprintf(buf, "%s discovers that (1,0) is ocean.", unitid(u));
    CuAssertStrEquals(tc, buf, u->faction->events->s);
}

static void test_movement_at_sea(CuTest * tc)
{
    unit * u;
    region *r1, *r2;
    faction * f;

    resetgame();
    r1 = createregion(0, 0);
    r1->terrain = T_OCEAN;
    r2 = createregion(1, 0);
    r2->terrain = T_PLAIN;
    u = createunit(r1);
    f = createfaction();
    u->faction = f;
    strcpy(u->thisorder, "move east");
    process_movement();
    CuAssertPtrEquals(tc, u, r1->units);
    CuAssertStrEquals(tc, "move east: Currently at sea.", f->mistakes->s);
}

int main(int argc, char** argv)
{
  CuString *output = CuStringNew();
  CuSuite *suite = CuSuiteNew();

  SUITE_ADD_TEST(suite, test_createregion);
  SUITE_ADD_TEST(suite, test_createregion_once);
  SUITE_ADD_TEST(suite, test_createunit);
  SUITE_ADD_TEST(suite, test_moveunit);
  SUITE_ADD_TEST(suite, test_destroyunit);
  SUITE_ADD_TEST(suite, test_movement);
  SUITE_ADD_TEST(suite, test_sailing);
  SUITE_ADD_TEST(suite, test_move_captain);
  SUITE_ADD_TEST(suite, test_movement_at_sea);
  SUITE_ADD_TEST(suite, test_movement_into_ocean);
  SUITE_ADD_TEST(suite, test_movement_invalid_direction);

  CuSuiteRun(suite);
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);
  printf("%s %s\n", argv[0], output->buffer);
  return suite->failCount;
}
