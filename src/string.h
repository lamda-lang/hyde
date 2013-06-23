#ifndef STRING_H
#define STRING_H

#include "api.h"

void *StringDecode(Byte **bytes, Error *error);
Value *StringEval(void *data, Code *code, bool pure, Error *error);
Value *StringCreateWithCharacters(Char *chars, Error *error);
void StringDealloc(Value *stringValue);
Integer64 StringHash(Value *stringValue);
bool StringEqual(Value *stringValue, Value *otherValue);
Value *StringConcatenate(Value *stringValue, Value *otherValue, Error *error);
Data *StringCreateDataWithASCIIEncoding(Value *stringValue, Error *error);

#endif
