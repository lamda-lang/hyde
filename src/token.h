#ifndef TOKEN_H
#define TOKEN_H

#include "api.h"

void *TokenDecode(Byte **bytes, Value **error);
Value *TokenCreateWithCharacters(Char *chars, Value **error);
void TokenDealloc(Value *tokenValue);
Integer64 TokenHash(Value *tokenValue);
Bool TokenEqual(Value *tokenValue, Value *otherValue);

extern Value *TokenOutOfMemoryError;
extern Value *TokenFileOpenError;
extern Value *TokenFileReadError;
extern Value *TokenFileWriteError;
extern Value *TokenFileCloseError;
extern Value *TokenInvalidTypeError;
extern Value *TokenArityMismatchError;

#endif
