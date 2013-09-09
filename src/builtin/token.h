#ifndef TOKEN_H
#define TOKEN_H

#include <runtime.h>

Value *TokenDecode(Byte **bytes, Error *error);
void TokenDealloc(Value *tokenValue);

#endif
