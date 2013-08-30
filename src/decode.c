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

Integer8 DecodeInteger8(Byte **bytes) {
    Integer8 value = **bytes;
    *bytes += 1;
    return value;
}

Integer32 DecodeInteger32(Byte **bytes) {
    Byte *blocks = *bytes;
    Integer32 value = 0;
    return (value = value << 0 | blocks[0] & 0X7F, *bytes += 1, blocks[0] & 0X80)
        && (value = value << 7 | blocks[1] & 0X7F, *bytes += 1, blocks[1] & 0X80)
        && (value = value << 7 | blocks[2] & 0X7F, *bytes += 1, blocks[2] & 0X80)
        && (value = value << 7 | blocks[3] & 0X7F, *bytes += 1, blocks[3] & 0X80)
        && (value = value << 7 | blocks[4] & 0XFF, *bytes += 1, blocks[4] & 0XFF), value;
}

Integer64 DecodeInteger64(Byte **bytes) {
    Byte *blocks = *bytes;
    Integer64 value = 0;
    return (value = value << 0 | blocks[0] & 0X7F, *bytes += 1, blocks[0] & 0X80)
        && (value = value << 7 | blocks[1] & 0X7F, *bytes += 1, blocks[1] & 0X80)
        && (value = value << 7 | blocks[2] & 0X7F, *bytes += 1, blocks[2] & 0X80)
        && (value = value << 7 | blocks[3] & 0X7F, *bytes += 1, blocks[3] & 0X80)
        && (value = value << 7 | blocks[4] & 0X7F, *bytes += 1, blocks[4] & 0X80)
        && (value = value << 7 | blocks[5] & 0X7F, *bytes += 1, blocks[5] & 0X80)
        && (value = value << 7 | blocks[6] & 0X7F, *bytes += 1, blocks[6] & 0X80)
        && (value = value << 7 | blocks[7] & 0X7F, *bytes += 1, blocks[7] & 0X80)
        && (value = value << 7 | blocks[8] & 0XFF, *bytes += 1, blocks[8] & 0XFF), value;
}

VALUE *DecodeValue(Byte **bytes, VALUE **error) {
    Integer8 code = DecodeInteger8(bytes);
    return decode[code](bytes, error);
}
