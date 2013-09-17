#ifndef BUILTIN_STRING_H
#define BUILTIN_STRING_H

#include <runtime.h>

typedef struct String String;

Value *StringDecode(Byte **bytes);
Value *StringEqual(String *string, String *other);
Size StringRelease(String *string);

#endif
