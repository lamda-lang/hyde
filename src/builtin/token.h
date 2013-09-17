#ifndef BUILTIN_TOKEN_H
#define BUILTIN_TOKEN_H

#include <runtime.h>

typedef struct Token Token;

Value *TokenDecode(Byte **bytes);
Value *TokenEqual(Token *token, Token *other);
Size TokenRelease(Token *token);

#endif
