#ifndef BUILTIN_TYPE_H
#define BUILTIN_TYPE_H

#include <runtime.h>

Value *TypeDecode(Byte **bytes);
void TypeRelease(Type *type);
Bool TypeEqual(Type *type, Type *other);

#endif
