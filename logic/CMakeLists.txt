cmake_minimum_required(VERSION 2.4)
project (logic)

include_directories (..)

set (MOCK_SRCS ../mock/region.c ../mock/unit.c ../mock/keyvalue.c ../mock/mock_svc.c)

add_executable (
  movement_test
  movement.c
  movement_test.c
  ../cutest/CuTest.c
  ${MOCK_SRCS}
)
