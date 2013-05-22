#include "nil.h"

struct Nil {
  Value base;
};

Value *NilValueBridge(Nil *nil) {
  return (Value *)nil;
}

Nil *NilCreate(void) {
  Size size = sizeof(struct Nil);
  Nil *nil = MemoryAlloc(size);
  if (nil == NULL) {
    goto error;
  }
  nil->base = ValueInit(TypeNil, FlagNone);
  return nil;

error:
  return NULL;
}

void NilDealloc(Value *nil) {
  MemoryDealloc(nil);
}

Integer64Bit NilHash(Value *nil) {
  return ValueType(nil);
}
