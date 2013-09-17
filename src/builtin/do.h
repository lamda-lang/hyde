#ifndef BUILTIN_DO_H
#define BUILTIN_DO_H

#include <runtime.h>

typedef struct Do Do;

Value *DoDecode(Byte **bytes);
Value *DoEval(Do *block, Value *context);
Value *DoEqual(Do *block, Do *other);
Size DoRelease(Do *block);

#endif
