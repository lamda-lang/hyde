#ifndef BUILTIN_TYPE_H
#define BUILTIN_TYPE_H

#include <runtime.h>

typedef struct Type Type;

Value *TypeDecode(Byte **bytes);
Size TypeRelease(Type *type);
Bool TypeEqual(Type *type, Type *other);

#endif
