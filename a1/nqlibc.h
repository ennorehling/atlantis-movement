#pragma once

#ifndef NOT_QUITE_LIBC_H
#define NOT_QUITE_LIBC_H

#include <stddef.h>

int strcmpl(const char *a, const char * b);
char * strlwr(char * a);
int memicmp(const char * a, const char * b, size_t s);
#endif
