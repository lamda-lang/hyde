#ifndef TOKEN_H
#define TOKEN_H

#include "api.h"

void *TokenDecode(Byte **bytes, Error *error);
Value *TokenEval(void *data, Code *code, Value **context, Bool pure, Error *error);
Value *TokenCreateWithCharacters(Char *chars, Error *error);
void TokenDealloc(Value *tokenValue);
Integer64 TokenHash(Value *tokenValue);
Bool TokenEqual(Value *tokenValue, Value *otherValue);

#endif
