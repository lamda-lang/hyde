#ifndef DO_H
#define DO_H

#include <runtime.h>

Value *DoDecode(Byte **bytes, Error *error);
Value *DoCreate(Kernel *kernel, Value **args, Integer8 count, Error *error);
void DoDealloc(Value *doValue);

#endif
