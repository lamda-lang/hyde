#ifndef BUILTIN_DO_H
#define BUILTIN_DO_H

#include <runtime.h>

Value *DoDecode(Byte **bytes);
void DoRelase(void *doData);
Bool DoEqual(void *doData, void *otherData);

#endif
