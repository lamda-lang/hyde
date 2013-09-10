#ifndef BUILTIN_STRING_H
#define BUILTIN_STRING_H

#include <runtime.h>

Value *StringDecode(Byte **bytes);
void StringRelease(void *stringData);
Bool StringEqual(void *stringData, void *otherData);

#endif
