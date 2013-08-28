#include "decode.h"

static Decode *decode[] = {
    [0] = BooleanDecodeTrue,
    [1] = BooleanDecodeFalse,
    [2] = CaseDecode,
    [3] = ComprehensionDecodeList,
    [4] = ComprehensionDecodeMap,
    [5] = ComprehensionDecodeSet,
    [6] = DoDecode,
    [7] = ElementDecode,
    [8] = FloatDecode,
    [9] = IntegerDecode,
    [10] = LamdaDecode,
    [11] = ListDecode,
    [12] = MapDecode,
    [13] = MemberDecode,
    [14] = NilDecode,
    [15] = ProtocolDecode,
    [16] = RangeDecode,
    [17] = ResultDecode,
    [18] = SetDecode,
    [19] = StringDecode,
    [20] = TokenDecode,
    [21] = TypeDecode,
    [22] = VariableDecode,
    [23] = WhenDecode
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
