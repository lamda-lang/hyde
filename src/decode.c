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

Integer8 DecodeInteger8(Byte **bytes) {
    return 0;
}

Integer16 DecodeInteger16(Byte **bytes) {
    return 0;
}

Integer32 DecodeInteger32(Byte **bytes) {
    return 0;
}

Integer64 DecodeInteger64(Byte **bytes) {
    return 0;
}

VALUE *DecodeValue(Byte **bytes, VALUE **error) {
    Integer8 code = DecodeInteger8(bytes);
    return decode[code](bytes, error);
}
