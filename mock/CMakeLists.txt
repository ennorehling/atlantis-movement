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

add_executable (svc_test ../svc/svc_test.c mock_svc.c ${CUTEST}/cutest/CuTest.c ${LIB_SRCS} ${LIB_HDRS} ${SVC_HDRS})

add_executable (mock_test mock_test.c ${CUTEST}/cutest/CuTest.c ${LIB_SRCS} ${LIB_HDRS})
