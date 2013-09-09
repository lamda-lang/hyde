#ifndef BUILTIN_STRING_H
#define BUILTIN_STRING_H

#include <runtime.h>

Value *StringDecode(Byte **bytes, Error *error);
void StringRelease(void *stringModel);
Bool StringEqual(void *stringModel, void *otherModel);

#endif
