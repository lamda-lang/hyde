#ifndef NIL_H
#define NIL_H

#include "api.h"

Nil *NilSingleton(void);

Value *NilValueBridge(void);

Integer64 NilHash(Value *nilValue);

#endif
