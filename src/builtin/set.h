#ifndef BUILTIN_SET_H
#define BUILTIN_SET_H

#include <runtime.h>

Value *SetDecode(Byte **bytes);
void SetRelease(void *setData);
Bool SetEqual(void *setData, void *otherData);

#endif
