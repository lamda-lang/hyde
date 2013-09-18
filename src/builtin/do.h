#ifndef BUILTIN_DO_H
#define BUILTIN_DO_H

#include <runtime.h>

typedef struct Do Do;

Do *DoDecode(Byte **bytes);
Value *DoEval(Do *block, Value *context);
Bool DoEqual(Do *block, Do *other);
Size DoRelease(Do *block);

#endif
