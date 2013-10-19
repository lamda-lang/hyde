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

Bool BinaryDecodeValue(Binary *binary, Integer32 *offset, Value **value) {
    Integer8 opcode;
    if (!BinaryDecodeInteger8(binary, offset, &opcode))
        return FALSE;
    switch (opcode) {
    case 0:
        return BinaryDecode(binary, offset, value);
    case 1:
        return BooleanDecode(binary, offset, value);
    case 2:
        return CaseDecode(binary, offset, value);
    case 3:
        return DoDecode(binary, offset, value);
    case 4:
        return FloatDecode(binary, offset, value);
    case 5:
        return IdentifierDecode(binary, offset, value);
    case 6:
        return IntegerDecode(binary, offset, value);
    case 7:
        return LamdaDecode(binary, offset, value);
    case 8:
        return ListDecode(binary, offset, value);
    case 9:
        return MapDecode(binary, offset, value);
    case 10:
        return ModuleDecode(binary, offset, value);
    case 11:
        return NilDecode(binary, offset, value);
    case 12:
        return ResultDecode(binary, offset, value);
    case 13:
        return SetDecode(binary, offset, value);
    case 14:
        return StringDecode(binary, offset, value);
    case 15:
        return TokenDecode(binary, offset, value);
    case 16:
        return WhenDecode(binary, offset, value);
    }
    return FALSE;
}
 
Bool BinaryDecode(Binary *binary, Integer32 *offset, Value **value) {
    Integer32 count;
    if (!BinaryDecodeInteger32(binary, offset, &count))
        return FALSE;
    if (*offset + count > binary->count)
        return FALSE; 
    Binary *result = BinaryCreate(count);
    for (Integer32 index = 0; index < binary->count; index += 1)
        result->bytes[index] = binary->bytes[index];
    *value = ValueCreateBinary(binary);
    return TRUE;
}

Value *BinaryEqual(Binary *binary, Binary *other) {
    if (binary->count != other->count)
        return BooleanCreate(FALSE);
    for (Integer32 index = 0; index < binary->count; index += 1)
        if (binary->bytes[index] != other->bytes[index])
            return BooleanCreate(FALSE);
    return BooleanCreate(TRUE);
}
