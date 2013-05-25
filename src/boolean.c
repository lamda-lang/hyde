#include "boolean.h"

struct Boolean {
  Value base;
  bool truth;
};

Value *BooleanValueBridge(Boolean *boolean) {
  return (Value *)boolean;
}

Boolean *BooleanCreate(bool truth) {
  Size size = sizeof(Boolean);
  Boolean *boolean = MemoryAlloc(size);
  if (boolean == NULL) {
    ExceptionRaise(ExceptionOutOfMemory);
    goto returnError;
  }
  boolean->base = ValueInit(TypeBoolean);
  boolean->truth = truth;
  return boolean;

returnError:
  return NULL;
}

void BooleanDealloc(Value *boolean) {
  MemoryDealloc(boolean);
}

Integer64Bit BooleanHash(Value *boolean) {
  Boolean *booleanBridge = ValueBooleanBridge(boolean);
  return booleanBridge->truth ? 1 : 0;
}
