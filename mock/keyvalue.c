#include "keyvalue.h"
#include <string.h>
#include <stdlib.h>

typedef struct keyvalue {
  struct keyvalue * next;
  char * key;
  void * value;
} keyvalue;

void * kv_set(struct keyvalue ** pkv, const char * key, void * value)
{
  struct keyvalue *kv;
  while (*pkv) {
    int cmp;
    kv = *pkv;
    cmp = strcmp(key, kv->key);
    if (cmp==0) {
      void * result = kv->value;
      kv->value = value;
      return result;
    } else if (cmp>0) {
      break;
    }
    pkv = &kv->next;
  }
  kv = malloc(sizeof(keyvalue));
  kv->next = *pkv;
  kv->key = strdup(key);
  kv->value = value;
  *pkv = kv;
  return 0;
}

void * kv_get(const struct keyvalue * root, const char * key)
{
  const struct keyvalue *kv = root;
  while (kv) {
    if (strcmp(key, kv->key)==0) return kv->value;
    kv = kv->next;
  }
  return 0;
}
