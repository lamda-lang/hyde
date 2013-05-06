#include "RTNil.h"

struct RTNil {
  RTBase base;
};

RTValue RTNilValueBridge(RTNil nil) {
  return (RTValue)nil;
}

RTNil RTNilCreate(void) {
  RTSize size = sizeof(struct RTNil);
  RTNil nil = RTMemoryAlloc(size);
  if (nil == NULL) {
    return NULL;
  }
  nil->base = RTBaseInit(RTTypeNil, RTFlagNone);
  return nil;
}

void RTNilDealloc(RTNil nil) {
  RTMemoryDealloc(nil);
}
