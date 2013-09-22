#ifndef TOKEN_H
#define TOKEN_H

#include "runtime.h"

Token *TokenDecode(Byte **bytes, Error *error);
Bool TokenEqual(Token *token, Token *other);
Size TokenRelease(Token *token);

#endif
