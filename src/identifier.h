#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "api.h"

Value *IdentifierCreateWithCharacters(Char *chars, Error *error);
void IdentifierDealloc(Value *idValue);
Value *IdentifierDecode(Byte **bytes, Error *error);
Integer64 IdentifierHash(Value *idValue);
bool IdentifierEqual(Value *idValue, Value *otherValue);
Value *IdentifierEval(Value *idValue, bool pure, Error *error);

#endif
