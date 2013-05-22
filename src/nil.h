#ifndef NIL_H
#define NIL_H

#include "runtime.h"

Value *NilValueBridge(Nil *nil);

Nil *NilCreate(void);

void NilDealloc(Value *nil_Nil);

Integer64Bit NilHash(Value *nil_Nil);

#endif
