#ifndef BUILTIN_STRING_H
#define BUILTIN_STRING_H

#include <runtime.h>

typedef struct String String;

Value *StringDecode(Byte **bytes);
Size StringRelease(String *string);
Bool StringEqual(String *string, String *other);

#endif
