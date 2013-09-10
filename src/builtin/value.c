#include <builtin/value.h>

static Decode *decode[] = {
    [0] = BooleanDecodeTrue,
    [1] = BooleanDecodeFalse,
    [2] = CaseDecode,
    [3] = ComprehensionDecodeList,
    [4] = ComprehensionDecodeMap,
    [5] = ComprehensionDecodeSet,
    [6] = DoDecode,
    [7] = FloatDecode,
    [8] = IdentifierDecode,
    [9] = IntegerDecode,
    [10] = LamdaDecode,
    [11] = ListDecode,
    [12] = MapDecode,
    [13] = ModuleDecode,
    [14] = NilDecode,
    [15] = ProtocolDecode,
    [16] = RangeDecode,
    [17] = ResultDecode,
    [18] = SetDecode,
    [19] = StringDecode,
    [20] = TokenDecode,
    [21] = TypeDecode,
    [22] = WhenDecode
};

struct Value {
    Builtin builtin;
    void *model;
}
