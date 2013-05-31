#ifndef DO_H
#define DO_H

#include "api.h"

Value *DoValueBridge(Do *block);

Do *DoDecode(Byte **bytes, Error *error);

void DoFetchContext(Do *block, Value **values, Byte **bytes);

void DoDealloc(Do *block);

Integer64 DoHash(Do *block);

#endif
