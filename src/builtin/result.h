#ifndef BUILTIN_RESULT_H
#define BUILTIN_RESULT_H

#include <runtime.h>

Value *ResultDecode(Byte **bytes);
void ResultRelease(void *resultData);
Bool ResultEqual(void *resultData, void *otherData);

#endif
