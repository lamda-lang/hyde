#ifndef BUILTIN_TOKEN_H
#define BUILTIN_TOKEN_H

#include <runtime.h>

Value *TokenDecode(Byte **bytes);
Bool TokenEqual(Token *token, Token *other);
void TokenRelease(Token *token);

#endif
