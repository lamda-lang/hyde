#include "RTBoolean.h"

#define RTFlagTrue RTFlagAlpha

struct RTBoolean {
  RTValue base;
};

RTValue *RTBooleanValueBridge(RTBoolean *boolean) {
  return (RTValue *)boolean;
}

RTBoolean *RTBooleanCreate(bool truth) {
  RTSize size = sizeof(RTBoolean);
  RTBoolean *boolean = RTMemoryAlloc(size);
  if (boolean == NULL) {
    goto error;
  }
  RTFlag mask = truth ? RTFlagTrue : RTFlagNone;
  boolean->base = RTValueInit(RTTypeBoolean, mask);
  return boolean;

error:
  return NULL;
}

void RTBooleanDealloc(RTValue *boolean) {
  RTMemoryDealloc(boolean);
}

RTInteger64Bit RTBooleanHash(RTValue *boolean) {
  return RTValueFlagSet(boolean, RTFlagTrue) ? 1 : 0;
}
