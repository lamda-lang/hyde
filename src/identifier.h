#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "api.h"

Value *IdentifierValueBridge(Identifier *id);

void IdentifierDealloc(Value *idValue);

Identifier *IdentifierDecode(Byte **bytes, Error *error);

Integer64 IdentifierHash(Value *idValue);

#endif
