cmake_minimum_required(VERSION 2.6)

if (WIN32)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE)
elseif (UNIX)
  add_definitions(-DLINUX)
  set(CMAKE_C_FLAGS "-g -Wall")
endif (WIN32)

add_subdirectory(mock)
add_subdirectory(logic)
add_subdirectory(a1)
