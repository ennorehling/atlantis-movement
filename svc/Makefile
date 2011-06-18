CFLAGS = -Wall -g
CC = gcc
CUTEST = ..
INCLUDES = -I$(CUTEST) -I.

all: tests

unit_test: unit_test.c game.h unit.h
	@$(CC) -o $@ unit_test.c $(CUTEST)/cutest/CuTest.c $(INCLUDES) $(CFLAGS)

tests: unit_test
	@./unit_test

clean:
	@rm -f *.o *~ *_test

