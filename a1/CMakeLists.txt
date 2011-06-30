cmake_minimum_required(VERSION 2.4)
project (a1 C)

set (CUTEST ..)

include_directories (..)
add_definitions(-DLOGIC)

set (LIB_SRCS atlantis.c nqlibc.c ../logic/movement.c atlantis_svc.c)

set (LIB_HDRS nqlibc.h atlantis.h)

add_definitions(-DCUSTOM_TESTS)
#add_definitions(-DCUSTOM_TESTS -DNEW_LOGIC)
add_executable (atlantis main.c ${LIB_SRCS} ${LIB_HDRS})
add_executable (atlantis_svc_test ../svc/svc_test.c atlantis_svc_test.c ${CUTEST}/cutest/CuTest.c ${LIB_SRCS} ${LIB_HDRS})
add_executable (atlantis_test atlantis_test.c ${CUTEST}/cutest/CuTest.c ${LIB_SRCS} ${LIB_HDRS})
add_test(atlantis_test atlantis_test)
add_test(atlantis_svc_test atlantis_svc_test)
