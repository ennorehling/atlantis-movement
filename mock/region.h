#ifndef MOCK_REGION_H
#define MOCK_REGION_H

struct keyvalue;

typedef struct region {
  struct region * next;
  int x, y;
  struct unit * units;
  struct keyvalue * stats;
} region;

struct region * r_create(int x, int y);
void r_destroy(struct region * r);
struct region * r_begin(void);
struct region * r_get(int x, int y);
#endif
