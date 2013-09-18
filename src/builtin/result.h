#ifndef BUILTIN_RESULT_H
#define BUILTIN_RESULT_H

#include <runtime.h>

typedef struct Result Result;

Result *ResultDecode(Byte **bytes);
Value *ResultEval(Result *result, Value *context);
Value *ResultEqual(Result *result, Result *other);
Size ResultRelease(Result *result);

#endif
