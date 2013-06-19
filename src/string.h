#ifndef STRING_H
#define STRING_H

#include "api.h"

Value *StringCreateWithCharacters(Char *chars, Error *error);

void StringDealloc(Value *stringValue);

Value *StringDecode(Byte **bytes, Error *error);

Integer64 StringHash(Value *stringValue);

Value *StringConcatenate(Value *stringValue, Value *otherValue, Error *error);

Value *StringEval(Value *stringValue, bool pure, Error *error);

#endif
