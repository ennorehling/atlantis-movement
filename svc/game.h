#pragma once
#ifndef SVC_INTERFACE_H
#define SVC_INTERFACE_H

struct iunit;
struct iregion;

typedef struct igame {
  struct iunit * units;
  struct iregion * regions;
  void (*reset)(void);
} igame;

extern struct igame svc;

#endif
