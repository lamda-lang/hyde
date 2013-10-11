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
    if (*offset + INTEGER_8_SIZE > bytes->count)
        return FALSE;
    *value = bytes[offset];
    *offset += INTEGER_8_SIZE;
    return TRUE;
}

Bool BinaryDecodeInteger32(Binary *binary, Integer32 *offset, Integer32 *value) {
    if (*offset + INTEGER_32_SIZE > bytes->count)
        return FALSE;
    Integer32 value[] = {
        bytes[*offset + 0],
        bytes[*offset + 1],
        bytes[*offset + 2],
        bytes[*offset + 3]
    };
    *value = value[0] << 24
           | value[1] << 16
           | value[2] << 8
           | value[3];
    *offset += INTEGER_32_SIZE;
    return TRUE;
}

Bool BinaryDecodeInteger64(Binary *binary, Integer32 *offset, Integer64 *value) {
    if (*offset + INTEGER_64_SIZE > bytes->count)
        return FALSE;
    Integer64 value[] = {
        bytes[*offset + 0],
        bytes[*offset + 1],
        bytes[*offset + 2],
        bytes[*offset + 3],
        bytes[*offset + 4],
        bytes[*offset + 5],
        bytes[*offset + 6],
        bytes[*offset + 7]
    };
    *value = value[0] << 56
           | value[1] << 48
           | value[2] << 40
           | value[3] << 32
           | value[4] << 24
           | value[5] << 16
           | value[6] << 8
           | value[7];
    *offset += INTEGER_64_SIZE;
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
}
 
Value *BinaryDecodePrimitive(Binary *binary, Integer32 *offset) {
    Integer32 count;
    if (!BinaryDecodeInteger32(binary, offset, &count))
        return NULL;
    if (*offset + count > binaty->count)
        return NULL; 
    Binary *result = BinaryCreate(count);
    MemoryCopyArray(binary->bytes, result->bytes, sizeof(Byte), count);
    return ValueCreateBinary(binary);
}

Value *BinaryDecodeKernel(Value **args) {
    Binary *binary = ValuePrimitive(args[0]).binaryValue;
    Integer32 offset = 0;
    Value *value = ValueDecode(binary, &offset);
    if (value == NULL)
        return ExceptionOutOfBounds(args[0]);
    return value;
}
