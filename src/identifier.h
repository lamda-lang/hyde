#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "api.h"

void *IdentifierDecode(Byte **bytes, Error *error);
Value *IdentifierEval(void *data, Code *code, bool pure, Error *error);
Value *IdentifierCreateWithCharacters(Char *chars, Error *error);
void IdentifierDealloc(Value *idValue);
Integer64 IdentifierHash(Value *idValue);
bool IdentifierEqual(Value *idValue, Value *otherValue);

#endif
