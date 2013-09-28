#ifndef STRING_H
#define STRING_H

#include "runtime.h"

Size StringSize(String *string);
Size StringEncode(String *string, Byte **bytes);
String *StringDecode(Byte **bytes, Error *error);
Value *StringEval(Value *value, String *string, Value *context, Error *error);
Bool StringEqual(String *string, String *other);
Size StringRelease(String *string);

#endif
