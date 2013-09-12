#ifndef BUILTIN_DO_H
#define BUILTIN_DO_H

#include <runtime.h>

Value *DoDecode(Byte **bytes);
void DoRelase(Do *block);
Bool DoEqual(Do *block, Do *other);

#endif
