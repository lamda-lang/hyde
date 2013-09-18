#ifndef BUILTIN_TYPE_H
#define BUILTIN_TYPE_H

#include <runtime.h>

typedef struct Type Type;

Type *TypeDecode(Byte **bytes);
Bool TypeEqual(Type *type, Type *other);
Size TypeRelease(Type *type);

#endif
