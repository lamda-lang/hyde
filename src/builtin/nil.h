#ifndef BUILTIN_NIL_H
#define BUILTIN_NIL_H

#include <runtime.h>

Value *NilDecode(Byte **bytes);
Bool NilEqual(void *nilData, void *otherData);

#endif
