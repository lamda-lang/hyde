#include "boolean.h"

#define FlagTrue FlagAlpha

struct Boolean {
  Value base;
};

Value *BooleanValueBridge(Boolean *boolean) {
  return (Value *)boolean;
}

Boolean *BooleanCreate(bool truth) {
  Size size = sizeof(Boolean);
  Boolean *boolean = MemoryAlloc(size);
  if (boolean == NULL) {
    goto error;
  }
  Flag mask = truth ? FlagTrue : FlagNone;
  boolean->base = ValueInit(TypeBoolean, mask);
  return boolean;

error:
  return NULL;
}

void BooleanDealloc(Value *boolean) {
  MemoryDealloc(boolean);
}

Integer64Bit BooleanHash(Value *boolean) {
  return ValueFlagSet(boolean, FlagTrue) ? 1 : 0;
}
