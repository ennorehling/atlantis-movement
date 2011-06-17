#ifndef MOCK_UNIT_H
#define MOCK_UNIT_H

struct keyvalue;

typedef struct unit {
  struct unit * next;
  int uid;
  struct keyvalue * stats;
} unit;

struct unit * u_create(void);

#endif
