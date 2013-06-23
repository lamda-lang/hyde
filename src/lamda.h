#ifndef LAMDA_H
#define LAMDA_H

#include "api.h"

void LamdaDealloc(Value *lamdaValue);
Integer64 LamdaHash(Value *lamdaValue);
void LamdaEnumerate(Value *lamdaValue, void (*callback)(Value *value));
Value *LamdaResult(Value *lamdaValue, Value **args, Integer8 argCount, Error *error);

#endif
