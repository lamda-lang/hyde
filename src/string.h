#ifndef STRING_H
#define STRING_H

#include "runtime.h"

Bool StringDecode(Binary *binary, Integer32 *offset, Value **value);
Bool StringEqual(String *string, String *other);

#endif
