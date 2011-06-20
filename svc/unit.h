#pragma once

#ifndef SVC_UNIT_H
#define SVC_UNIT_H

struct unit;
struct region;

typedef struct iunit {
  struct unit * (*create)(void);
  void (*destroy)(struct unit * u);
  struct unit * (*get)(int id);

  int (*get_uid)(const struct unit *);
  struct region * (*get_region)(const struct unit *);
  void (*set_region)(struct unit *, struct region *);
  
  int (*get_moves)(const struct unit *, struct region * result[], int offset, int n);
  int (*get_movement_speed)(const struct unit *);
} iunit;

#endif
