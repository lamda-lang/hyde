#ifndef TOKEN_H
#define TOKEN_H

#include "api.h"

VALUE *TokenDecode(Byte **bytes, Error *error);
void TokenDealloc(VALUE *tokenValue);

#endif
