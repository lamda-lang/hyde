#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "api.h"

Value *IdentifierValueBridge(Identifier *id);

void IdentifierDealloc(Value *id);

Identifier *IdentifierDecode(Byte **bytes, Exception *exception);

Integer64 IdentifierHash(Value *id);

#endif
