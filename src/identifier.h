#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "api.h"

Value *IdentifierValueBridge(Identifier *id);

void IdentifierDealloc(Value *id_Identifier);

Identifier *IdentifierDecode(Byte **data);

Integer64Bit IdentifierHash(Value *id_Identifier);

#endif
