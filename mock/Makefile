CFLAGS = -Wall -Werror -g
CC = gcc
CUTEST = ..
INCLUDES = -I$(CUTEST) -I.

all: tests

LIB_SRCS = region.c unit.c keyvalue.c
LIB_HDRS = region.h unit.h keyvalue.h
LIB_TEST = region_test.c unit_test.c keyvalue_test.c

SVC_TEST = ../svc/game_test.c ../svc/unit_test.c ../svc/region_test.c ../svc/svc_test.c
SVC_HDRS = ../svc/game.h ../svc/unit.h ../svc/region.h

mock_test: mock_test.c $(LIB_SRCS) $(LIB_HDRS) $(LIB_TEST)
	@$(CC) -o $@ mock_test.c $(LIB_SRCS) $(CUTEST)/cutest/CuTest.c $(INCLUDES) $(CFLAGS)

svc_test: mock_svc.c $(LIB_SRCS) $(LIB_HDRS) $(LIB_TEST) $(SVC_TEST) $(SVC_HDRS)
	@$(CC) -o $@ mock_svc.c ../svc/svc_test.c $(LIB_SRCS) $(CUTEST)/cutest/CuTest.c $(INCLUDES) $(CFLAGS)
  
tests: mock_test svc_test
	@./mock_test
	@./svc_test

clean:
	@rm -f *.o *~ *_test

