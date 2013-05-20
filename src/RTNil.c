#include "RTNil.h"

struct RTNil {
  RTValue base;
};

RTValue *RTNilValueBridge(RTNil *nil) {
  return (RTValue *)nil;
}

RTNil *RTNilCreate(void) {
  RTSize size = sizeof(struct RTNil);
  RTNil *nil = RTMemoryAlloc(size);
  if (nil == NULL) {
    goto error;
  }
  nil->base = RTValueInit(RTTypeNil, RTFlagNone);
  return nil;

error:
  return NULL;
}

void RTNilDealloc(RTValue *nil) {
  RTMemoryDealloc(nil);
}

RTInteger64Bit RTNilHash(RTValue *nil) {
  return RTValueType(nil);
}
