#ifndef BINARY_H
#define BINARY_H

#include "runtime.h"

Value *BinaryCreateValue(Byte *bytes, Integer32 count);
Bool BinaryDecodeInteger8(Binary *binary, Integer32 *offset, Integer8 *value);
Bool BinaryDecodeInteger32(Binary *binary, Integer32 *offset, Integer32 *value);
Bool BinaryDecodeInteger64(Binary *binary, Integer32 *offset, Integer64 *value);
Bool BinaryDecodeFloat64(Binary *binary, Integer32 *offset, Float64 *value);
Bool BinaryDecodeBool(Binary *binary, Integer32 *offset, Bool *value);
Value *BinaryDecodeValue(Binary *binary, Integer32 *offset);
Value *BinaryDecode(Binary *binary, Integer32 *offset);
Value *BinaryEqual(Binary *binary, Binary *other);

#endif
