#ifndef BUILTIN_TOKEN_H
#define BUILTIN_TOKEN_H

#include <builtin/api.h>
#include <posix/api.h>
#include <util/api.h>

VALUE *TokenDecode(Byte **bytes, Error *error);
void TokenDealloc(VALUE *tokenValue);

#endif
