CFLAGS = -Wall -g
CC = gcc
CUTEST = ..
INCLUDES = -I$(CUTEST) -I.

all: keyvalue_test

keyvalue_test: keyvalue_test.c keyvalue.c keyvalue.h
	$(CC) -o $@ keyvalue_test.c keyvalue.c $(CUTEST)/cutest/CuTest.c $(INCLUDES) $(CFLAGS)

clean:
	@rm -f *.o *~ keyvalue_test

