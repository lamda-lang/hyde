#ifndef LAMDA_H
#define LAMDA_H

#include "api.h"

void *LamdaDecode(Byte **bytes, Error *error);
Value *LamdaEval(void *data, Code *code, Value **context, Bool pure, Error *error);
void LamdaDealloc(Value *lamdaValue);
Integer64 LamdaHash(Value *lamdaValue);
Integer8 LamdaArity(Value *lamdaValue);
void LamdaEnumerate(Value *lamdaValue, void (*callback)(Value *value));
Value **LamdaCreateContext(Value *lamdaValue, Error *error);
void LamdaDeallocContext(Value **context);
Value *LamdaResult(Value *lamdaValue, Value **context, Error *error);

#endif
