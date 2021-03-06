#ifndef TOKEN_H
#define TOKEN_H

#include "runtime.h"

Bool TokenDecode(Binary *binary, Integer32 *offset, Value **value);
Bool TokenEqual(Token *token, Token *other);

#endif
