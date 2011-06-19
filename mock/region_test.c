#include "../platform.h"
#include "region.h"
#include <cutest/CuTest.h>

static void setup_region()
{
  region * r;
  while ((r = r_begin())!=0) {
    r_destroy(r);
  }
}

static void test_region_create(CuTest * tc)
{
  region * r;
  
  setup_region();

  r = r_create(1, 2);
  
  CuAssertPtrNotNull(tc, r);
  CuAssertPtrEquals(tc, 0, r->stats);
  CuAssertPtrEquals(tc, 0, r->units);

  CuAssertIntEquals(tc, 1, r->x);
  CuAssertIntEquals(tc, 2, r->y);
}

static void test_region_destroy(CuTest * tc) {
  region * r;
  setup_region();
  r = r_create(1, 2);
  CuAssertPtrEquals(tc, r, r_begin());
  r_destroy(r);
  CuAssertPtrEquals(tc, 0, r_begin());
}

static void test_region_create_same_twice(CuTest * tc)
{
  region * r1, * r2;

  setup_region();

  r1 = r_create(1, 2);
  r2 = r_create(1, 2);
  CuAssertPtrEquals(tc, r1, r2);
}

static void test_region_list(CuTest * tc)
{
  region * r1, * r2;

  setup_region();
  
  r1 = r_create(0, 1);
  r2 = r_create(1, 2);
  CuAssertTrue(tc, r1->next==0 || r2->next==0);
  CuAssertTrue(tc, r1->next==r2 || r2->next==r1);
}

static void test_region_iteration(CuTest * tc)
{
  region * r;
  int i;
  
  setup_region();
  
  for (i=0;i!=16;++i) {
    r_create(0, i);
  }
  for (r=r_begin();r;r=r->next) {
    --i;
  }
  CuAssertIntEquals(tc, 0, i);
}

static void test_region_get(CuTest * tc)
{
  region * r;
  
  setup_region();
  
  r = r_create(0, 1);
  CuAssertPtrEquals(tc, r, r_get(0, 1));
  CuAssertPtrEquals(tc, 0, r_get(0, 0));
}

void add_region_tests(CuSuite *suite)
{
  SUITE_ADD_TEST(suite, test_region_create);
  SUITE_ADD_TEST(suite, test_region_destroy);
  SUITE_ADD_TEST(suite, test_region_create_same_twice);
  SUITE_ADD_TEST(suite, test_region_list);
  SUITE_ADD_TEST(suite, test_region_iteration);
  SUITE_ADD_TEST(suite, test_region_get);
}
