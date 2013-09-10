#ifndef BUILTIN_TOKEN_H
#define BUILTIN_TOKEN_H

#include <runtime.h>

Value *TokenDecode(Byte **bytes);
Bool TokenEqual(void *tokenData, void *otherData);
void TokenRelease(void *tokenData);

#endif
