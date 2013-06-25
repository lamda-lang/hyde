#ifndef DO_H
#define DO_H

#include "api.h"

void *DoDecode(Byte **bytes, Error *error);
Value *DoEval(void *data, Code *code, Value **context, bool pure, Error *error);
void DoDealloc(Value *doValue);
Integer64 DoHash(Value *doValue);
void DoEnumerate(Value *doValue, void (*callback)(Value *value));

#endif
