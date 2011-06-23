cmake_minimum_required(VERSION 2.4)
project (atlantis1)

include_directories (..)
add_definitions(-DLOGIC)
if (WIN32)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE)
#  include_directories (../libc/win32)
#  add_subdirectory (../libc/win32 libc)
elseif (UNIX)
  add_definitions(-DLINUX)
#  include_directories(../libc/glibc)
#  add_subdirectory (../libc/glibc libc)
## hack
#  set(CMAKE_C_FLAGS "-g -Wall")
  set(CMAKE_C_FLAGS "-g")
else (WIN32)
  include_directories(../libc/default)
  add_subdirectory (../libc/default libc)
endif (WIN32)
#include_directories (../libc/default)

set (SERVER_SRCS
 atlantis1.c
)

set (SERVER_HDRS
)

add_executable (atlantis ${SERVER_SRCS} ${SERVER_HDRS})
if (WIN32)
#  target_link_libraries (atlantis oly-libc)
elseif (UNIX)
  target_link_libraries (atlantis m)
endif (WIN32)
