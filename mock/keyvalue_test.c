#include "../platform.h"
#include "keyvalue.h"
#include <cutest/CuTest.h>
#include <stdio.h>

static void test_keyvalue_get_set(CuTest * tc)
{
  struct keyvalue * kv = 0;
  const char * a = "dolly";
  const char * b = "world";

  CuAssertPtrEquals(tc, 0, kv_get(kv, "hello"));
  CuAssertPtrEquals(tc, 0, kv_set(&kv, "hello", (void *)a));
  CuAssertPtrNotNull(tc, kv);
  CuAssertPtrEquals(tc, 0, kv_set(&kv, "goodbye", (void *)a));

  CuAssertPtrEquals(tc, (void *)a, kv_get(kv, "hello"));
  CuAssertPtrEquals(tc, (void *)a, kv_set(&kv, "hello", (void *)b));
  CuAssertPtrEquals(tc, (void *)b, kv_set(&kv, "hello", (void *)b));

  CuAssertPtrEquals(tc, (void *)b, kv_set(&kv, "hello", 0));
  CuAssertPtrEquals(tc, 0, kv_get(kv, "hello"));
}

static void test_keyvalue_geti_seti(CuTest * tc)
{
  struct keyvalue * kv = 0;

  CuAssertIntEquals(tc, 0, kv_geti(kv, "hello"));
  CuAssertIntEquals(tc, 0, kv_seti(&kv, "hello", 4));
  CuAssertIntEquals(tc, 4, kv_geti(kv, "hello"));
  CuAssertIntEquals(tc, 4, kv_seti(&kv, "hello", 3));
  CuAssertIntEquals(tc, 3, kv_geti(kv, "hello"));
}

void add_keyvalue_tests(CuSuite *suite)
{
  SUITE_ADD_TEST(suite, test_keyvalue_get_set);
  SUITE_ADD_TEST(suite, test_keyvalue_geti_seti);
}
