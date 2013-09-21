#ifndef RESULT_H
#define RESULT_H

#include "runtime.h"

Result *ResultDecode(Byte **bytes);
Value *ResultEval(Result *result, Value *context);
Bool ResultEqual(Result *result, Result *other);
Size ResultRelease(Result *result);

#endif
