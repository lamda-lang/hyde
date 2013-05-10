#include "RTBoolean.h"

enum {
  RTImplementationBase = RTImplementationAlpha,
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
  RTFlag mask = truth ? RTFlagPositive : RTFlagNone;
  boolean->base = RTValueInit(RTTypeBoolean, RTImplementationBase, mask);
  return boolean;
}

void RTBooleanDealloc(RTBoolean *boolean) {
  RTMemoryDealloc(boolean);
}
