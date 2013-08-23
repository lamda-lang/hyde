#ifndef STRING_H
#define STRING_H

#include "api.h"

void *StringDecode(Byte **bytes, Value **error);
Value *StringCreateWithCharacters(Char *chars, Value **error);
void StringDealloc(Value *stringValue);
Integer64 StringHash(Value *stringValue);
Bool StringEqual(Value *stringValue, Value *otherValue);

/* kernels */
Value *StringConcatenate(Value **args, Integer8 count, Value **error);
Value *StringPrint(Value **args, Integer8 count, Value **error);

#endif
