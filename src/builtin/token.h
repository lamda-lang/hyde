#ifndef BUILTIN_TOKEN_H
#define BUILTIN_TOKEN_H

#include <runtime.h>

Value *TokenDecode(Byte **bytes, Error *error);
Bool TokenEqual(void *tokenModel, void *otherModel);
void TokenRelease(void *tokenModel);

#endif
