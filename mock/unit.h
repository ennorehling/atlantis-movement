#ifndef MOCK_UNIT_H
#define MOCK_UNIT_H

struct keyvalue;
struct region;

typedef struct unit {
  struct unit * next;
  int uid;
  struct keyvalue * stats;
} unit;

struct unit * u_create(void);
void u_destroy(struct unit * u);
struct unit * u_get(int id);

void u_set_moves(struct unit * u, struct region * path[]);
int u_get_moves(const struct unit * u, struct region * result[], int offset, int n);
void u_free_all(void);

#endif
