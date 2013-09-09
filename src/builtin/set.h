#ifndef SET_H
#define SET_H

#include <runtime.h>

Value *SetDecode(Byte **bytes, Error *error);
void SetDealloc(Value *setValue);

#endif
