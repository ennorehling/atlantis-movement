#ifndef MOCK_REGION_H
#define MOCK_REGION_H

#define MAXDIRECTIONS 6

struct keyvalue;

typedef struct region {
  struct region * next;
  int x, y;
  struct unit * units;
  struct keyvalue * stats;
} region;

void r_free_all(void);
struct region * r_create(int x, int y);
void r_destroy(struct region * r);
struct region * r_begin(void);
struct region * r_get(int x, int y);
void r_add_unit(struct region * r, struct unit * u);
void r_remove_unit(struct region * r, struct unit * u);

#endif
