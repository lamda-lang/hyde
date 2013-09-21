#ifndef DO_H
#define DO_H

#include "runtime.h"

Do *DoDecode(Byte **bytes);
Value *DoEval(Do *block, Value *context);
Bool DoEqual(Do *block, Do *other);
Size DoRelease(Do *block);

#endif
