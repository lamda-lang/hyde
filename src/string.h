#ifndef STRING_H
#define STRING_H

#include "runtime.h"

Value *StringValueBridge(String *string);

void StringDealloc(Value *string_String);

String *StringDecode(Byte **data);

Integer64Bit StringHash(Value *string_String);

String *StringConcatenate(String *string, String *other);

void StringEnumerateCodepoints(String *string, void (*block)(Integer32Bit codepoint));

#endif
