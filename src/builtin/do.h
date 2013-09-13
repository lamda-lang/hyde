#ifndef BUILTIN_DO_H
#define BUILTIN_DO_H

#include <runtime.h>

typedef struct Do Do;

Value *DoDecode(Byte **bytes);
Size DoRelease(Do *block);
Bool DoEqual(Do *block, Do *other);

#endif
