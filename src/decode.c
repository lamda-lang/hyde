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
    [12] = MemberDecode,
    [13] = NilDecode,
    [14] = ProtocolDecode,
    [15] = RangeDecode,
    [16] = ResultDecode,
    [17] = SetDecode,
    [18] = StringDecode,
    [19] = TokenDecode,
    [20] = TypeDecode,
    [21] = VariableDecode,
    [22] = WhenDecode
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
