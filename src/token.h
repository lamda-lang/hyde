#ifndef TOKEN_H
#define TOKEN_H

#include "runtime.h"

Token *TokenDecode(Byte **bytes);
Bool TokenEqual(Token *token, Token *other);
Size TokenRelease(Token *token);

#endif
