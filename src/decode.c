#include "decode.h"

typedef VALUE *Decode(Byte **bytes, VALUE **error);

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
    [14] = ModuleDecode,
    [15] = NilDecode,
    [16] = ProtocolDecode,
    [17] = RangeDecode,
    [18] = ResultDecode,
    [19] = SetDecode,
    [20] = StringDecode,
    [21] = TokenDecode,
    [22] = TypeDecode,
    [23] = VariableDecode,
    [24] = WhenDecode
};

static Integer8 DecodeCount(Byte **bytes) {
    return 0;
}

Integer8 DecodeInteger8(Byte **bytes) {
    Integer8 value = **bytes;
    *bytes += 1;
    return value;
}

Integer32 DecodeInteger32(Byte **bytes) {
    return 0;
}

Integer64 DecodeInteger64(Byte **bytes) {
    Byte *blocks = *bytes;
    Integer64 value = blocks[0] & 0X7F;
    switch (DecodeCount(bytes)) {
    case 0XFF: ;
    case 0X7F: ;
    case 0X3F: ;
    case 0X1F: ;
    case 0X0F: ;
    case 0X07: ;
    case 0X03: ;
    case 0X01: ;
    }
    return value;
}

VALUE *DecodeValue(Byte **bytes, VALUE **error) {
    Integer8 code = DecodeInteger8(bytes);
    return decode[code](bytes, error);
}
