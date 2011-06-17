#ifndef MOCK_REGION_H
#define MOCK_REGION_H

struct keyvalue;

typedef struct region {
  struct region * next;
  int x, y;
  struct keyvalue * stats;
} region;

struct region * r_create(int x, int y);

#endif
