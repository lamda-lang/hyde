#ifndef BUILTIN_DO_H
#define BUILTIN_DO_H

#include <builtin/api.h>
#include <posix/api.h>
#include <util/api.h>

VALUE *DoDecode(Byte **bytes, Error *error);
VALUE *DoCreate(Kernel *kernel, VALUE **args, Integer8 count, Error *error);
void DoDealloc(VALUE *doValue);

#endif
