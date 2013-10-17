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

Value *BinaryCreateValue(Byte *bytes, Integer32 count) {
    Binary *binary = BinaryCreate(count);
    for (Integer32 index = 0; index < count; index += 1)
        binary->bytes[index] = bytes[index];
    return ValueCreateBinary(binary);
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
        return BinaryDecode(binary, offset);
    case 1:
        return BooleanDecode(binary, offset);
    case 2:
        return CaseDecode(binary, offset);
    case 3:
        return DoDecode(binary, offset);
    case 4:
        return FloatDecode(binary, offset);
    case 5:
        return IdentifierDecode(binary, offset);
    case 6:
        return IntegerDecode(binary, offset);
    case 7:
        return LamdaDecode(binary, offset);
    case 8:
        return ListDecode(binary, offset);
    case 9:
        return MapDecode(binary, offset);
    case 10:
        return ModuleDecode(binary, offset);
    case 11:
        return NilDecode(binary, offset);
    case 12:
        return RangeDecode(binary, offset);
    case 13:
        return ResultDecode(binary, offset);
    case 14:
        return SetDecode(binary, offset);
    case 15:
        return StringDecode(binary, offset);
    case 16:
        return TokenDecode(binary, offset);
    case 17:
        return TypeDecode(binary, offset);
    case 18:
        return WhenDecode(binary, offset);
    }
    return NULL;
}
 
Value *BinaryDecode(Binary *binary, Integer32 *offset) {
    Integer32 count;
    if (!BinaryDecodeInteger32(binary, offset, &count))
        return NULL;
    if (*offset + count > binary->count)
        return NULL; 
    Binary *result = BinaryCreate(count);
    for (Integer32 index = 0; index < binary->count; index += 1)
        result->bytes[index] = binary->bytes[index];
    return ValueCreateBinary(binary);
}

Value *BinaryEqual(Binary *binary, Binary *other) {
    if (binary->count != other->count)
        return BooleanCreate(FALSE);
    for (Integer32 index = 0; index < binary->count; index += 1)
        if (binary->bytes[index] != other->bytes[index])
            return BooleanCreate(FALSE);
    return BooleanCreate(TRUE);
}
