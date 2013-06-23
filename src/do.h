#ifndef DO_H
#define DO_H

#include "api.h"

void DoDealloc(Value *doValue);
Integer64 DoHash(Value *doValue);
void DoEnumerate(Value *doValue, void (*callback)(Value *value));

#endif
