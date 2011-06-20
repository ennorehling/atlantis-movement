#ifndef MOCK_KEYVALUE_H
#define MOCK_KEYVALUE_H

struct keyvalue;

void * kv_set(struct keyvalue ** pkv, const char * key, void * value);
void * kv_get(const struct keyvalue * kv, const char * key);

int kv_seti(struct keyvalue ** pkv, const char * key, int value);
int kv_geti(const struct keyvalue * kv, const char * key);

#endif
