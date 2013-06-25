#ifndef STRING_H
#define STRING_H

#include "api.h"

void *StringDecode(Byte **bytes, Error *error);
Value *StringEval(void *data, Code *code, Value **context, bool pure, Error *error);
Value *StringCreateWithCharacters(Char *chars, Error *error);
void StringDealloc(Value *stringValue);
Integer64 StringHash(Value *stringValue);
bool StringEqual(Value *stringValue, Value *otherValue);

/* kernels */
Value *StringConcatenate(Value **args, Integer8 count, Error *error);
Value *StringPrint(Value **args, Integer8 count, Error *error);

#endif
