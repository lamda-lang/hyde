#ifndef DO_H
#define DO_H

#include "api.h"

Value *DoValueBridge(Do *block);

Do *DoDecode(Byte **bytes, Error *error);

void DoDealloc(Do *block);

Integer64 DoHash(Do *block);

#endif
