#pragma once

#ifndef SVC_CURSOR_H
#define SVC_CURSOR_H

typedef struct icursor {
  void (*destroy)(void * cursor);

  int (*get)(void * cursor, int n, void * results[]);
  int (*advance)(void ** cursor, int n);
} icursor;

#endif
