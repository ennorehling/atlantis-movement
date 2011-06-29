#pragma once
#ifndef SVC_INTERFACE_H
#define SVC_INTERFACE_H

struct iunit;
struct icursor;
struct iregion;

typedef struct igame {
  struct iunit * units;
  struct iregion * regions;
  
  int max_directions;

  void (*reset)(void);
  void * (*get_regions)(struct icursor **);
  void (*add_event)(const char * name, ...);
} igame;

extern struct igame svc;

#endif
