#include "decode.h"

Integer8 DecodeInteger8(Byte **bytes) {
    Integer8 value = **bytes;
    *bytes += 1;
    return value;
}

Integer32 DecodeInteger32(Byte **bytes) {
    Byte *blocks = *bytes;
    Integer32 value = blocks[0] & 0X7F;
    if (~blocks[0] & 0X80)
        return *bytes += 1, value;
    value = value << 7 | (blocks[1] & 0X7F);
    if (~blocks[1] & 0X80)
        return *bytes += 2, value;
    value = value << 7 | (blocks[2] & 0X7F);
    if (~blocks[2] & 0X80)
        return *bytes += 3, value;
    value = value << 7 | (blocks[3] & 0X7F);
    if (~blocks[3] & 0X80)
        return *bytes += 4, value;
    return *bytes += 5, value << 7 | blocks[4];
}

Integer64 DecodeInteger64(Byte **bytes) {
    Byte *blocks = *bytes;
    Integer32 value = blocks[0] & 0X7F;
    if (~blocks[0] & 0X80)
        return *bytes += 1, value;
    value = value << 7 | (blocks[1] & 0X7F);
    if (~blocks[1] & 0X80)
        return *bytes += 2, value;
    value = value << 7 | (blocks[2] & 0X7F);
    if (~blocks[2] & 0X80)
        return *bytes += 3, value;
    value = value << 7 | (blocks[3] & 0X7F);
    if (~blocks[3] & 0X80)
        return *bytes += 4, value;
    value = value << 7 | (blocks[4] & 0X7F);
    if (~blocks[4] & 0X80)
        return *bytes += 5, value;
    value = value << 7 | (blocks[5] & 0X7F);
    if (~blocks[5] & 0X80)
        return *bytes += 6, value;
    value = value << 7 | (blocks[6] & 0X7F);
    if (~blocks[6] & 0X80)
        return *bytes += 7, value;
    value = value << 7 | (blocks[7] & 0X7F);
    if (~blocks[7] & 0X80)
        return *bytes += 8, value;
    return *bytes += 9, value << 7 | blocks[8];
}

Float64 DecodeFloat64(Byte **bytes) {
    Integer64 binary = DecodeInteger64(bytes);
    Float64 value = 0;
    MemoryCopy(&binary, &value, 8);
    return value;
}
