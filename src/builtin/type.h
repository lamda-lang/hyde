#ifndef BUILTIN_TYPE_H
#define BUILTIN_TYPE_H

#include <runtime.h>

Value *TypeDecode(Byte **bytes);
void TypeRelease(void *typeData);
Bool TypeEqual(void *typeData, void *otherData);

#endif
