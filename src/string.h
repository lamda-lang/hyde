#ifndef STRING_H
#define STRING_H

#include "api.h"

Value *StringValueBridge(String *string);

void StringDealloc(Value *string);

String *StringDecode(Byte **bytes, Exception *exception);

Integer64 StringHash(Value *string);

String *StringConcatenate(String *string, String *other, Exception *exception);

void StringEnumerateCodepoints(String *string, void (*block)(Integer32 codepoint));

#endif
