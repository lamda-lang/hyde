#ifndef BUILTIN_WHEN_H
#define BUILTIN_WHEN_H

#include <runtime.h>

Value *WhenDecode(Byte **bytes);
void WhenRelease(void *whenData);
Bool WhenEqual(void *whenData, void *otherData);

#endif
