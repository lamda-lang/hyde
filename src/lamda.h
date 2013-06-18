#ifndef LAMDA_H
#define LAMDA_H

#include "api.h"

Value *LamdaValueBridge(Lamda *lamda);

Value *LamdaDecode(Byte **bytes, Error *error);

void LamdaFetch(Value *lamdaValue, Value **values);

void LamdaDealloc(Value *lamdaValue);

Integer64 LamdaHash(Value *lamdaValue);

void LamdaEnumerate(Value *lamdaValue, void (*callback)(Value *value));

Value *LamdaEval(Value *lamdaValue, bool pure, Error *error);

Value *LamdaResult(Lamda *lamda, Value **args, Integer8 argCount, Error *error);

#endif
