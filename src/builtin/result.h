#ifndef BUILTIN_RESULT_H
#define BUILTIN_RESULT_H

#include <runtime.h>

typedef struct Result Result;

Value *ResultDecode(Byte **bytes);
Value *ResultEval(Result *result, Value *context);
Size ResultRelease(Result *result);
Bool ResultEqual(Result *result, Result *other);

#endif
