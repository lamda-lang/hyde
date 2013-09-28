#ifndef BINARY_H
#define BINARY_H

#include "runtime.h"

Size BinarySize(Binary *binary);
Size BinaryEncode(Binary *binary, Byte **bytes);
Binary *BinaryDecode(Byte **bytes, Error *error);
Value *BinaryEval(Value *value, Binary *binary, Value *context, Error *error);
Bool BinaryEqual(Binary *binary, Binary *other);
Size BinaryRelease(Binary *binary);

#endif
