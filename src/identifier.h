#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "api.h"

Value *IdentifierValueBridge(Identifier *id);

void IdentifierDealloc(Value *idValue);

Identifier *IdentifierDecode(Byte **bytes, Exception *exception);

Integer64 IdentifierHash(Value *idValue);

#endif
