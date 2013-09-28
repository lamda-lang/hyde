#ifndef RESULT_H
#define RESULT_H

#include "runtime.h"

Size ResultSize(Result *result);
Size ResultEncode(Result *result, Byte **bytes);
Result *ResultDecode(Byte **bytes, Error *error);
Value *ResultEval(Value *value, Result *result, Value *context, Error *error);
Bool ResultEqual(Result *result, Result *other);
Size ResultRelease(Result *result);

#endif
