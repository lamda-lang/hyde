#ifndef STRING_H
#define STRING_H

#include "runtime.h"

Size StringSize(String *string);
String *StringDecode(Byte **bytes, Error *error);
Bool StringEqual(String *string, String *other);
Size StringRelease(String *string);

#endif
