#include "decode.h"

Integer8 DecodeInteger8FLE(Byte **bytes) {
    Integer8 value = **bytes;
    *bytes += 1;
    return value;
}

Integer16 DecodeInteger16FLE(Byte **bytes) {
    Byte *byte = *bytes;
    Integer16 value[] = {byte[0], byte[1]};
    value[1] <<= 8;
    *bytes += 2;
    return value[0] | value[1];
}

Integer32 DecodeInteger32FLE(Byte **bytes) {
    Byte *byte = *bytes;
    Integer32 value[] = {byte[0], byte[1], byte[2], byte[3]};
    value[1] <<= 8;
    value[2] <<= 16;
    value[3] <<= 24;
    *bytes += 4;
    return value[0] | value[1] | value[2] | value[3];
}

Integer64 DecodeInteger64FLE(Byte **bytes) {
    Byte *byte = *bytes;
    Integer64 value[] = {byte[0], byte[1], byte[2], byte[3], byte[4], byte[5], byte[6], byte[7]};
    value[1] <<= 8;
    value[2] <<= 16;
    value[3] <<= 24;
    value[4] <<= 32;
    value[5] <<= 40;
    value[6] <<= 48;
    value[7] <<= 56;
    *bytes += 8;
    return value[0] | value[1] | value[2] | value[3] | value[4] | value[5] | value[6] | value[7];
}

Integer32 DecodeInteger32VLE(Byte **bytes) {
    Integer32 result = 0;
    bool more = true;
    for (Index index = 0; more; index += 1) {
        Integer32 value = (**bytes & 0X7F);
        result |= value << index * 7;
        more = (**bytes & 0X80) != 0; 
        *bytes += 1;
    }
    return result;
}

Float64 DecodeFloat64FLE(Byte **bytes) {
    union {
	Float64 IEEE754;
	Integer64 binary;
    } punner = {.binary = DecodeInteger64FLE(bytes)};
    return punner.IEEE754;;
}