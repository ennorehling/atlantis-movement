#pragma once
#ifndef SVC_INTERFACE_H
#define SVC_INTERFACE_H

struct iunit;
struct icursor;
struct iregion;

typedef struct igame {
  struct iunit * units;
  struct iregion * regions;

  void (*reset)(void);
  void * (*get_regions)(struct icursor **);
} igame;

extern struct igame svc;

#endif
