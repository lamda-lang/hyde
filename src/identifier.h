#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "api.h"

void *IdentifierDecode(Byte **bytes, Error *error);
Value *IdentifierEval(void *data, Code *code, Value **context, Bool pure, Error *error);
Value *IdentifierCreateWithCharacters(Char *chars, Error *error);
void IdentifierDealloc(Value *idValue);
Integer64 IdentifierHash(Value *idValue);
Bool IdentifierEqual(Value *idValue, Value *otherValue);

#endif
