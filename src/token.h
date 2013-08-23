#ifndef TOKEN_H
#define TOKEN_H

#include "runtime.h"

void *TokenDecode(Byte **bytes, VALUE **error);
VALUE *TokenCreateWithCharacters(Char *chars, VALUE **error);
void TokenDealloc(VALUE *tokenVALUE);
Integer64 TokenHash(VALUE *tokenVALUE);
Bool TokenEqual(VALUE *tokenVALUE, VALUE *otherVALUE);

extern VALUE *TokenOutOfMemoryError;
extern VALUE *TokenFileOpenError;
extern VALUE *TokenFileReadError;
extern VALUE *TokenFileWriteError;
extern VALUE *TokenFileCloseError;
extern VALUE *TokenInvalidTypeError;
extern VALUE *TokenArityMismatchError;

#endif
