#ifndef BUILTIN_TOKEN_H
#define BUILTIN_TOKEN_H

#include <runtime.h>

typedef struct Token Token;

Token *TokenDecode(Byte **bytes);
Bool TokenEqual(Token *token, Token *other);
Size TokenRelease(Token *token);

#endif
