#ifndef STRING_H
#define STRING_H

#include "api.h"

Value *StringValueBridge(String *string);

void StringDealloc(Value *stringValue);

String *StringDecode(Byte **bytes, Error *error);

Integer64 StringHash(Value *stringValue);

Integer32 StringLength(String *string);

Integer32 *StringCodepoints(String *string);

String *StringConcatenate(String *string, String *other, Error *error);

#endif
