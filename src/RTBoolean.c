#include "RTBoolean.h"

enum {
  RTFlagPositive = RTFlagAlpha
};

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
  boolean->base = RTValueInit(RTTypeBoolean) | RTValueMask(RTFlagPositive, truth);
  return boolean;
}

void RTBooleanDealloc(RTBoolean *boolean) {
  RTMemoryDealloc(boolean);
}
