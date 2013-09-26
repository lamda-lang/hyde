#include "binary.h"

struct Binary {
    Integer32 count;
    Byte bytes[];
};

static Size BinarySizeOf(Integer32 count) {
    return sizeof(Binary) + sizeof(Byte) * count;
}

static Binary *BinaryCreate(Integer32 count, Error *error) {
    Size size = BinarySizeOf(count);
    Binary *binary = MemoryAlloc(size, error);
    if (ERROR(error))
        return NULL;
    binary->count = count;
    return binary;
}

Size BinarySize(Binary *binary) {
    return INTEGER_32_SIZE + binary->count;
}

Size BinaryEncode(Binary *binary, Byte **bytes) {
    EncodeInteger32(binary->count, bytes);
    MemoryCopy(binary->bytes, *bytes, binary->count);
    *bytes += binary->count;
    return BinarySize(binary);
}

Binary *BinaryDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32(bytes);
    Binary *binary = BinaryCreate(count, error);
    if (ERROR(error))
        return NULL;
    MemoryCopy(*bytes, binary->bytes, count);
    *bytes += count;
    return binary;
}

Bool BinaryEqual(Binary *binary, Binary *other) {
    return binary->count == other->count
        && MemoryEqual(binary->bytes, other->bytes, binary->count);
}

Size BinaryRelease(Binary *binary) {
    Size size = BinarySizeOf(binary->count);
    MemoryDealloc(binary);
    return size;
}
