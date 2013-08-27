#include "decode.h"

static Decode *decode[] = {
    [0] = BooleanDecodeTrue,
    [1] = BooleanDecodeFalse,
    [2] = CaseDecode,
    [3] = ComprehensionDecodeList,
    [4] = ComprehensionDecodeMap,
    [5] = ComprehensionDecodeSet,
    [6] = DoDecode,
    [7] = FloatDecode,
    [8] = IntegerDecode,
    [9] = LamdaDecode,
    [10] = ListDecode,
    [11] = MapDecode,
    [12] = NilDecode,
    [13] = ProtocolDecode,
    [14] = RangeDecode,
    [15] = ResultDecode,
    [16] = SetDecode,
    [17] = StringDecode,
    [18] = TokenDecode,
    [19] = TypeDecode,
    [20] = VariableDecode,
    [21] = WhenDecode
};

Integer8 DecodeInteger8FLE(Byte **bytes) {
    Integer8 value = **bytes;
    *bytes += 1;
    return value;
}

Integer16 DecodeInteger16FLE(Byte **bytes) {
    Integer16 value[] = {
        (*bytes)[0],
        (*bytes)[1]
    };
    value[1] <<= 8;
    *bytes += 2;
    return value[0]
         | value[1];
}

Integer32 DecodeInteger32FLE(Byte **bytes) {
    Integer32 value[] = {
        (*bytes)[0],
        (*bytes)[1],
        (*bytes)[2],
        (*bytes)[3]
    };
    value[1] <<= 8;
    value[2] <<= 16;
    value[3] <<= 24;
    *bytes += 4;
    return value[0]
         | value[1]
         | value[2]
         | value[3];
}

Integer64 DecodeInteger64FLE(Byte **bytes) {
    Integer64 value[] = {
        (*bytes)[0],
        (*bytes)[1],
        (*bytes)[2],
        (*bytes)[3],
        (*bytes)[4],
        (*bytes)[5],
        (*bytes)[6],
        (*bytes)[7]
    };
    value[1] <<= 8;
    value[2] <<= 16;
    value[3] <<= 24;
    value[4] <<= 32;
    value[5] <<= 40;
    value[6] <<= 48;
    value[7] <<= 56;
    *bytes += 8;
    return value[0]
         | value[1]
         | value[2]
         | value[3]
         | value[4]
         | value[5]
         | value[6]
         | value[7];
}

Integer32 DecodeInteger32VLE(Byte **bytes) {
    Integer32 result = 0;
    Bool more = TRUE;
    for (Integer8 index = 0; more; index += 1) {
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
        Integer64 integer64;
    } binary = {
        .integer64 = DecodeInteger64FLE(bytes)
    };
    return binary.IEEE754;
}

VALUE *DecodeValue(Byte **bytes, VALUE **error) {
    Integer8 code = DecodeInteger8FLE(bytes);
    return decode[code](bytes, error);
}
