#ifndef BUILTIN_DO_H
#define BUILTIN_DO_H

#include <runtime.h>

typedef struct Do Do;

Value *DoDecode(Byte **bytes);
Value *DoEval(Do *block, Value *context);
Size DoRelease(Do *block);
Bool DoEqual(Do *block, Do *other);

#endif
