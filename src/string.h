#ifndef STRING_H
#define STRING_H

#include "api.h"

Value *StringValueBridge(String *string);

void StringDealloc(Value *stringValue);

Value *StringDecode(Byte **bytes, Error *error);

Integer64 StringHash(Value *stringValue);

String *StringConcatenate(String *string, String *other, Error *error);

Value *StringEval(Value *stringValue, Error *error);

#endif
