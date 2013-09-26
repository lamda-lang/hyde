#ifndef TYPE_H
#define TYPE_H

#include "runtime.h"

Size TypeSize(Type *type);
Size TypeEncode(Type *type, Byte **bytes);
Type *TypeDecode(Byte **bytes, Error *error);
Bool TypeEqual(Type *type, Type *other);
Size TypeRelease(Type *type);

#endif
