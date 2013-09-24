#include "encode.h"

void EncodeInteger8(Integer8 value, Byte **bytes) {
    **bytes = value;
    *bytes += sizeof(Integer8);
}

void EncodeInteger16(Integer16 value, Byte **bytes) {
    Byte *blocks = *bytes;
    blocks[0] = value >> 8 & 0XFF;
    blocks[1] = value & 0XFF;
    *bytes += sizeof(Integer16);
}

void EncodeInteger32(Integer32 value, Byte **bytes) {
    Byte *blocks = *bytes;
    blocks[0] = value >> 24 & 0XFF;
    blocks[1] = value >> 16 & 0XFF;
    blocks[2] = value >> 8 & 0XFF;
    blocks[3] = value & 0XFF;
    *bytes += sizeof(Integer32);
}

void EncodeInteger64(Integer64 value, Byte **bytes) {
    Byte *blocks = *bytes;
    blocks[0] = value >> 56 & 0XFF;
    blocks[1] = value >> 48 & 0XFF;
    blocks[2] = value >> 40 & 0XFF;
    blocks[3] = value >> 32 & 0XFF;
    blocks[4] = value >> 24 & 0XFF;
    blocks[5] = value >> 16 & 0XFF;
    blocks[6] = value >> 8 & 0XFF;
    blocks[7] = value & 0XFF;
    *bytes += sizeof(Integer64);
}

void EncodeFloat64(Float64 value, Byte **bytes) {
    Integer64 binary = 0;
    MemoryCopy(&value, &binary, sizeof(Integer64));
    EncodeInteger64(binary, bytes);
}
