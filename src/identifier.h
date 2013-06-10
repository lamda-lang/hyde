#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "api.h"

Value *IdentifierValueBridge(Identifier *id);

void IdentifierDealloc(Value *idValue);

Value *IdentifierDecode(Byte **bytes, Error *error);

Integer64 IdentifierHash(Value *idValue);

Value *IdentifierEval(Value *idValue, Error *error);

#endif
