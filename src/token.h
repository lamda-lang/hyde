#ifndef TOKEN_H
#define TOKEN_H

#include "runtime.h"

Size TokenSize(Token *token);
Size TokenEncode(Token *token, Byte **bytes);
Token *TokenDecode(Byte **bytes, Error *error);
Value *TokenEval(Value *value, Token *token, Value *context, Error *error);
Bool TokenEqual(Token *token, Token *other);
Size TokenRelease(Token *token);

#endif
