#ifndef DO_H
#define DO_H

#include <runtime.h>

VALUE *DoDecode(Byte **bytes, Error *error);
VALUE *DoCreate(Kernel *kernel, VALUE **args, Integer8 count, Error *error);
void DoDealloc(VALUE *doValue);

#endif
