#ifndef DO_H
#define DO_H

#include "runtime.h"

Do *DoDecode(Byte **bytes, Error *error);
Value *DoEval(Do *block, Value *context, Error *error);
Bool DoEqual(Do *block, Do *other);
Size DoRelease(Do *block);

#endif
