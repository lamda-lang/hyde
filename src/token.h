#ifndef TOKEN_H
#define TOKEN_H

#include "runtime.h"

VALUE *TokenDecode(Byte **bytes, VALUE **error);
void TokenDealloc(VALUE *tokenValue);

#endif
