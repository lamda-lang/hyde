#ifndef BUILTIN_LAMDA_H
#define BUILTIN_LAMDA_H

#include <builtin/api.h>
#include <posix/api.h>
#include <util/api.h>

VALUE *LamdaDecode(Byte **bytes, Error *error);
VALUE *LamdaCreate(Kernel *kernel, Integer8 arity, Error *error);
void LamdaDealloc(VALUE *lamdaValue);

#endif
