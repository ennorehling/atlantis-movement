#pragma once

#ifndef SVC_REGION_H
#define SVC_REGION_H

struct unit;
struct region;

struct icursor;

typedef struct iregion {
  struct region * (*create)(int x, int y);
  void (*destroy)(struct region * r);

  struct region * (*get_at)(int x, int y);

  void (*get_xy)(const struct region *, int * x, int * y);
  void (*get_adj)(const struct region *, struct region * result[]);
  void * (*get_units)(const struct region *, struct icursor ** ic);
  void (*add_unit)(struct region *, struct unit *);
  void (*remove_unit)(struct region *, struct unit *);
} iregion;

#endif
