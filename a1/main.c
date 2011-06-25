#include "atlantis1.h"
#include <stdio.h>

int main (int argc, char ** argv)
{
	puts ("Atlantis v1.0  " __DATE__ "\n"
			"Copyright 1993 by Russell Wallace.\n"
			"Type ? for list of commands.");
	return interactive();
}
