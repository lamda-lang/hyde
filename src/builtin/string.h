#ifndef BUILTIN_STRING_H
#define BUILTIN_STRING_H

#include <runtime.h>

Value *StringDecode(Byte **bytes);
void StringRelease(String *string);
Bool StringEqual(String *string, String *other);

#endif
