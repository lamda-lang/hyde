#ifndef STRING_H
#define STRING_H

#include "runtime.h"

String *StringDecode(Byte **bytes);
Bool StringEqual(String *string, String *other);
Size StringRelease(String *string);

#endif
