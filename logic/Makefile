CFLAGS = -Wall -g
CC = gcc
CUTEST = ..
INCLUDES = -I$(CUTEST) -I.

all: tests

MOCK_SRCS = ../mock/region.c ../mock/unit.c ../mock/keyvalue.c
MOCK_HDRS = ../mock/region.h ../mock/unit.h ../mock/keyvalue.h

LIB_SRCS = movement.c
LIB_TEST = movement_test.c

SVC_HDRS = ../svc/game.h ../svc/unit.h ../svc/region.h

movement_test: movement_test.c movement.c $(SVC_HDRS) $(MOCK_HDRS) $(MOCK_SRCS)
	@$(CC) -o $@ movement_test.c movement.c $(MOCK_SRCS) $(CUTEST)/cutest/CuTest.c $(INCLUDES) $(CFLAGS)

tests: movement_test
	@./movement_test

clean:
	@rm -f *.o *~ *_test

