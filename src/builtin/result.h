#ifndef BUILTIN_RESULT_H
#define BUILTIN_RESULT_H

#include <runtime.h>

Value *ResultDecode(Byte **bytes);
void ResultRelease(Result *result);
Bool ResultEqual(Result *result, Result *other);

#endif
