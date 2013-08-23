#ifndef LAMDA_H
#define LAMDA_H

#include "api.h"

void *LamdaDecode(Byte **bytes, Value **error);
void LamdaDealloc(Value *lamdaValue);
Integer64 LamdaHash(Value *lamdaValue);
Integer8 LamdaArity(Value *lamdaValue);
void LamdaEnumerate(Value *lamdaValue, void (*callback)(Value *value));
Value **LamdaCreateContext(Value *lamdaValue, Value **error);
void LamdaDeallocContext(Value **context);
Value *LamdaResult(Value *lamdaValue, Value **context, Value **error);

#endif
