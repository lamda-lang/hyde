#ifndef LAMDA_H
#define LAMDA_H

#include "api.h"

void *LamdaDecode(Byte **bytes, Error *error);
Value *LamdaEval(void *data, Code *code, bool pure, Error *error);
void LamdaDealloc(Value *lamdaValue);
Integer64 LamdaHash(Value *lamdaValue);
void LamdaEnumerate(Value *lamdaValue, void (*callback)(Value *value));
Value *LamdaResult(Value *lamdaValue, Value **args, Integer8 argCount, Error *error);

#endif
