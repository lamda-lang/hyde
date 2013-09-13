#ifndef BUILTIN_RESULT_H
#define BUILTIN_RESULT_H

#include <runtime.h>

typedef struct Result Result;

Value *ResultDecode(Byte **bytes);
Size ResultRelease(Result *result);
Bool ResultEqual(Result *result, Result *other);

#endif
