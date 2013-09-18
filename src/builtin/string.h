#ifndef BUILTIN_STRING_H
#define BUILTIN_STRING_H

#include <runtime.h>

typedef struct String String;

String *StringDecode(Byte **bytes);
Bool StringEqual(String *string, String *other);
Size StringRelease(String *string);

#endif
