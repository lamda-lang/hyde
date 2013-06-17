#include "execute.h"

static Instruction *instruction[] = {
    [0] = NilDecode,
    [1] = BooleanDecodeTrue,
    [2] = BooleanDecodeFalse,
    [3] = IntegerDecode,
    [4] = FloatDecode,
    [5] = IdentifierDecode,
    [6] = StringDecode,
    [7] = RangeDecode,
    [8] = SetDecode,
    [9] = ListDecode,
    [10] = MapDecode,
    [11] = ModuleDecode,
    [12] = WhenDecode,
    [13] = CaseDecode,
    [14] = ResultDecode,
    [15] = DoDecode,
    [16] = LambdaDecode
};

Status ExecuteCode(Byte *bytes, Value **values, Integer32 valueCount, Error *error) {
    for (Integer32 index = 0; index < valueCount; index += 1) {
        Integer8 opcode = DecodeInteger8FLE(&bytes);
	Integer32 valueIndex = DecodeInteger32VLE(&bytes);
	Value *value = instruction[opcode](&bytes, error);
	if (value == NULL) {
	    goto returnError;
	}
	values[valueIndex] = value;
    }
    return StatusSuccess;

returnError:
    return StatusFailure;
}
