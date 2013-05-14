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
    return NULL;
  }
  RTFlag mask = truth ? RTFlagTrue : RTFlagNone;
  boolean->base = RTValueInit(RTTypeBoolean, mask);
  return boolean;
}

void RTBooleanDealloc(RTBoolean *boolean) {
  RTMemoryDealloc(boolean);
}

bool RTBooleanEqual(RTBoolean *boolean, RTBoolean *other) {
  return RTValueBaseFlagSet(boolean->base, RTFlagTrue) == RTValueBaseFlagSet(other->base, RTFlagTrue);
}

RTInteger64Bit RTBooleanHash(RTBoolean *boolean) {
  return RTValueBaseFlagSet(boolean->base, RTFlagTrue) ? 1 : 0;
}
