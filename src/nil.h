#ifndef NIL_H
#define NIL_H

#include "api.h"

Value *NilSingleton(void);

Integer64 NilHash(Value *nilValue);

Value *NilDecode(Byte **bytes, Error *error);

Value *NilEval(Value *nilValue, bool pure, Error *error);

#endif
