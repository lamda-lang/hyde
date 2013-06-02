#ifndef DO_H
#define DO_H

#include "api.h"

Value *DoValueBridge(Do *block);

Do *DoDecode(Byte **bytes, Error *error);

Integer8 DoContextCount(Do *block);

void DoSetContextValueAtIndex(Do *block, Value *value, Integer8 index);

void DoDealloc(Value *doValue);

Integer64 DoHash(Value *doValue);

void DoEnumerate(Value *doValue, void (*block)(Value *value));

#endif
