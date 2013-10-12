#ifndef BINARY_H
#define BINARY_H

#include "runtime.h"

Bool BinaryDecodeInteger8(Binary *binary, Integer32 *offset, Integer8 *value);
Bool BinaryDecodeInteger32(Binary *binary, Integer32 *offset, Integer32 *value);
Bool BinaryDecodeInteger64(Binary *binary, Integer32 *offset, Integer64 *value);
Bool BinaryDecodeFloat64(Binary *binary, Integer32 *offset, Float64 *value);
Bool BinaryDecodeBool(Binary *binary, Integer32 *offset, Bool *value);
Value *BinaryDecodeValue(Binary *binary, Integer32 *offset);
Value *BinaryDecodePrimitive(Binary *binary, Integer32 *offset);
Value *BinaryDecodeKernel(Value **args);

#endif
