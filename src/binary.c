#include "binary.h"

struct Binary {
    Integer32 count;
    Byte bytes[];
};

static Binary *BinaryCreate(Integer32 count) {
    Binary *binary = MemoryAllocRegion(sizeof(Binary), sizeof(Byte), count);
    binary->count = count;
    return binary;
}

Bool BinaryDecodeInteger8(Binary *binary, Integer32 *offset, Integer8 *value) {
    if (*offset + INTEGER_8_SIZE > binary->count)
        return FALSE;
    *value = binary->bytes[*offset];
    *offset += INTEGER_8_SIZE;
    return TRUE;
}

Bool BinaryDecodeInteger32(Binary *binary, Integer32 *offset, Integer32 *value) {
    if (*offset + INTEGER_32_SIZE > binary->count)
        return FALSE;
    Byte *bytes = binary->bytes + *offset;
    Integer32 blocks[] = {
        bytes[0],
        bytes[1],
        bytes[2],
        bytes[3]
    };
    *value = blocks[0] << 24
           | blocks[1] << 16
           | blocks[2] << 8
           | blocks[3];
    *offset += INTEGER_32_SIZE;
    return TRUE;
}

Bool BinaryDecodeInteger64(Binary *binary, Integer32 *offset, Integer64 *value) {
    if (*offset + INTEGER_64_SIZE > binary->count)
        return FALSE;
    Byte *bytes = binary->bytes + *offset;
    Integer64 blocks[] = {
        bytes[0],
        bytes[1],
        bytes[2],
        bytes[3],
        bytes[4],
        bytes[5],
        bytes[6],
        bytes[7]
    };
    *value = blocks[0] << 56
           | blocks[1] << 48
           | blocks[2] << 40
           | blocks[3] << 32
           | blocks[4] << 24
           | blocks[5] << 16
           | blocks[6] << 8
           | blocks[7];
    *offset += INTEGER_64_SIZE;
    return TRUE;
}

Bool BinaryDecodeFloat64(Binary *binary, Integer32 *offset, Float64 *value) {
    /* missing */
    *value = 0.0;
    *offset += FLOAT_64_SIZE;
    return TRUE;
}

Bool BinaryDecodeBool(Binary *binary, Integer32 *offset, Bool *value) {
    if (*offset + BOOL_SIZE > binary->count)
        return FALSE;
    *value = binary->bytes[*offset] == 0 ? FALSE : TRUE;
    *offset += BOOL_SIZE;
    return TRUE;
}

Value *BinaryDecodeValue(Binary *binary, Integer32 *offset) {
    Integer8 opcode;
    if (!BinaryDecodeInteger8(binary, offset, &opcode))
        return NULL;
    switch (opcode) {
    case 0:
        return BinaryDecodePrimitive(binary, offset);
    case 1:
        return BooleanDecodePrimitive(binary, offset);
    case 2:
        return CaseDecodePrimitive(binary, offset);
    case 3:
        return DoDecodePrimitive(binary, offset);
    case 4:
        return FloatDecodePrimitive(binary, offset);
    case 5:
        return IdentifierDecodePrimitive(binary, offset);
    case 6:
        return IntegerDecodePrimitive(binary, offset);
    case 7:
        return LamdaDecodePrimitive(binary, offset);
    case 8:
        return ListDecodePrimitive(binary, offset);
    case 9:
        return MapDecodePrimitive(binary, offset);
    case 10:
        return ModuleDecodePrimitive(binary, offset);
    case 11:
        return NilDecodePrimitive(binary, offset);
    case 12:
        return RangeDecodePrimitive(binary, offset);
    case 13:
        return ResultDecodePrimitive(binary, offset);
    case 14:
        return SetDecodePrimitive(binary, offset);
    case 15:
        return StringDecodePrimitive(binary, offset);
    case 16:
        return TokenDecodePrimitive(binary, offset);
    case 17:
        return TypeDecodePrimitive(binary, offset);
    case 18:
        return WhenDecodePrimitive(binary, offset);
    }
    return NULL;
}
 
Value *BinaryDecodePrimitive(Binary *binary, Integer32 *offset) {
    Integer32 count;
    if (!BinaryDecodeInteger32(binary, offset, &count))
        return NULL;
    if (*offset + count > binary->count)
        return NULL; 
    Binary *result = BinaryCreate(count);
    MemoryCopyArray(binary->bytes, result->bytes, sizeof(Byte), count);
    return ValueCreateBinary(binary);
}

Value *BinaryDecodeKernel(Value **args) {
    Binary *binary = ValueBinaryPrimitive(args[0]);
    Integer32 offset = 0;
    Value *value = BinaryDecodeValue(binary, &offset);
    if (value == NULL)
        /* missing */
        return NULL;
    return value;
}
