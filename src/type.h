#ifndef TYPE_H
#define TYPE_H

#include "runtime.h"

Type *TypeDecode(Byte **bytes);
Bool TypeEqual(Type *type, Type *other);
Size TypeRelease(Type *type);

#endif
