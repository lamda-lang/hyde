#ifndef LAMDA_H
#define LAMDA_H

#include <runtime.h>

VALUE *LamdaDecode(Byte **bytes, Error *error);
VALUE *LamdaCreate(Kernel *kernel, Integer8 arity, Error *error);
void LamdaDealloc(VALUE *lamdaValue);

#endif
