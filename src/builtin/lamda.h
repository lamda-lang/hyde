#ifndef LAMDA_H
#define LAMDA_H

#include <runtime.h>

Value *LamdaDecode(Byte **bytes, Error *error);
Value *LamdaCreate(Kernel *kernel, Integer8 arity, Error *error);
void LamdaDealloc(Value *lamdaValue);

#endif
