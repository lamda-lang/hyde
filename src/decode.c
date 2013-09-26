#include "decode.h"

Integer8 DecodeInteger8(Byte **bytes) {
    Integer8 value = **bytes;
    *bytes += INTEGER_8_SIZE;
    return value;
}

Integer16 DecodeInteger16(Byte **bytes) {
    Byte *blocks = *bytes;
    Integer16 value = blocks[0];
    value = value << 8 | blocks[1];
    *bytes += INTEGER_16_SIZE;
    return value;
}

Integer32 DecodeInteger32(Byte **bytes) {
    Byte *blocks = *bytes;
    Integer32 value = blocks[0];
    value = value << 8 | blocks[1];
    value = value << 8 | blocks[2];
    value = value << 8 | blocks[3];
    *bytes += INTEGER_32_SIZE;
    return value;
}

Integer64 DecodeInteger64(Byte **bytes) {
    Byte *blocks = *bytes;
    Integer64 value = blocks[0];
    value = value << 8 | blocks[1];
    value = value << 8 | blocks[2];
    value = value << 8 | blocks[3];
    value = value << 8 | blocks[4];
    value = value << 8 | blocks[5];
    value = value << 8 | blocks[6];
    value = value << 8 | blocks[7];
    *bytes += INTEGER_64_SIZE;
    return value;
}

Float64 DecodeFloat64(Byte **bytes) {
    Integer64 binary = DecodeInteger64(bytes);
    Float64 value = 0;
    MemoryCopy(&binary, &value, INTEGER_64_SIZE);
    return value;
}

Bool DecodeBool(Byte **bytes) {
    return DecodeInteger8(bytes) == 0 ? FALSE : TRUE;
}
