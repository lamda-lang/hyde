#ifndef DO_H
#define DO_H

#include "api.h"

Value *DoValueBridge(Do *block);

Value *DoDecode(Byte **bytes, Error *error);

void DoFetch(Value *doValue, Value **values);

void DoDealloc(Value *doValue);

Integer64 DoHash(Value *doValue);

void DoEnumerate(Value *doValue, void (*callback)(Value *value));

Value *DoEval(Value *doValue, Error *error);

#endif
