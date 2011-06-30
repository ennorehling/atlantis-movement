cmake_minimum_required(VERSION 2.4)
project (mock)

set (CUTEST ..)

include_directories (..)

set (LIB_SRCS
 region.c unit.c keyvalue.c
)

set (LIB_HDRS
 region.h unit.h keyvalue.h
)

set (SVC_TEST
  ../svc/game_test.c ../svc/unit_test.c ../svc/region_test.c ../svc/svc_test.c
)
set (SVC_HDRS
  ../svc/game.h ../svc/unit.h ../svc/region.h
)

set (MOCK_TESTS keyvalue_test.c region_test.c unit_test.c)

add_executable (mock_svc_test ../svc/svc_test.c mock_svc.c ${CUTEST}/cutest/CuTest.c ${LIB_SRCS} ${LIB_HDRS} ${SVC_HDRS})
add_executable (mock_test mock_test.c ${MOCK_TESTS} ${CUTEST}/cutest/CuTest.c ${LIB_SRCS} ${LIB_HDRS})
add_test (mock_test mock_test)
add_test (mock_svc_test mock_svc_test)
