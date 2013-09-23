#include "decode.h"

Integer8 DecodeInteger8(Byte **bytes) {
}

Integer16 DecodeInteger16(Byte **bytes) {
}

Integer32 DecodeInteger32(Byte **bytes) {
}

Integer64 DecodeInteger64(Byte **bytes) {
}

Float64 DecodeFloat64(Byte **bytes) {
    Integer64 binary = DecodeInteger64(bytes);
    Float64 value = 0;
    MemoryCopy(&binary, &value, 8);
    return value;
}
