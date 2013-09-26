#ifndef CONSTANT_H
#define CONSTANT_H

#include "runtime.h"

void ConstantInit(Error *error);
Value *ConstantValue(Constant constant);
void ConstantDealloc(void);

#endif
