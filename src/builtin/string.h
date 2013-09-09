#ifndef STRING_H
#define STRING_H

#include <runtime.h>

Value *StringDecode(Byte **bytes, Error *error);
void StringDealloc(Value *stringValue);

#endif
