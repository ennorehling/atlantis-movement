CFLAGS = -Wall -g
CC = gcc
CUTEST = ..
INCLUDES = -I$(CUTEST) -I.

all: tests

keyvalue_test: keyvalue_test.c keyvalue.c keyvalue.h
	@$(CC) -o $@ keyvalue_test.c keyvalue.c $(CUTEST)/cutest/CuTest.c $(INCLUDES) $(CFLAGS)

unit_test: unit_test.c unit.c unit.h
	@$(CC) -o $@ unit_test.c unit.c $(CUTEST)/cutest/CuTest.c $(INCLUDES) $(CFLAGS)

region_test: region_test.c region.c region.h
	@$(CC) -o $@ region_test.c region.c $(CUTEST)/cutest/CuTest.c $(INCLUDES) $(CFLAGS)

tests: keyvalue_test unit_test region_test
	@./keyvalue_test
	@./unit_test
	@./region_test

clean:
	@rm -f *.o *~ *_test

