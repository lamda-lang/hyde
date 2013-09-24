#include "decode.h"

Integer8 DecodeInteger8(Byte **bytes) {
    Integer8 value = **bytes;
    *bytes += sizeof(Integer8);
    return value;
}

Integer16 DecodeInteger16(Byte **bytes) {
    Byte *blocks = *bytes;
    Integer16 value = blocks[0];
    value = value << 8 | blocks[1];
    *bytes += sizeof(Integer16);
    return value;
}

Integer32 DecodeInteger32(Byte **bytes) {
    Byte *blocks = *bytes;
    Integer32 value = blocks[0];
    value = value << 8 | blocks[1];
    value = value << 8 | blocks[2];
    value = value << 8 | blocks[3];
    *bytes += sizeof(Integer32);
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
    *bytes += sizeof(Integer64);
    return value;
}

Float64 DecodeFloat64(Byte **bytes) {
    Integer64 binary = DecodeInteger64(bytes);
    Float64 value = 0;
    MemoryCopy(&binary, &value, sizeof(Integer64));
    return value;
}
