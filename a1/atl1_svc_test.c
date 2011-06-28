#include <svc/game.h>
#include <svc/unit.h>
#include <svc/region.h>
#include "atlantis1.h"
#include <cutest/CuTest.h>
#include <string.h>

void test_get_moves_a1(CuTest * tc)
{
    unit * u;
    region *r1, *r2;
    region * path[2];

    resetgame();

    r1 = createregion(0, 0);
    r1->terrain = T_OCEAN;
    r2 = createregion(1, 0);
    r2->terrain = T_PLAIN;
    u = createunit(r1);

    strcpy(u->thisorder, "move east");
    CuAssertIntEquals(tc, 1, svc.units->get_moves(u, path, 0, 2));
    CuAssertPtrEquals(tc, r2, path[0]);

    strcpy(u->thisorder, "move east west");
    CuAssertIntEquals(tc, 2, svc.units->get_moves(u, path, 0, 2));
    CuAssertPtrEquals(tc, r2, path[0]);
    CuAssertPtrEquals(tc, r1, path[1]);

    strcpy(u->thisorder, "move east west east");
    CuAssertIntEquals(tc, -1, svc.units->get_moves(u, path, 0, 2));
    CuAssertPtrEquals(tc, r2, path[0]);
    CuAssertPtrEquals(tc, r1, path[1]);

    CuAssertIntEquals(tc, 2, svc.units->get_moves(u, path, 1, 2));
    CuAssertPtrEquals(tc, r1, path[0]);
    CuAssertPtrEquals(tc, r2, path[1]);
}

void add_custom_tests(CuSuite * suite)
{
    SUITE_ADD_TEST(suite, test_get_moves_a1);
}
