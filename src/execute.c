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
    [8] = RangeDecodeUpper,
    [9] = RangeDecodeLower,
    [10] = SetDecode,
    [11] = ListDecode,
    [12] = MapDecode,
    [13] = ModuleDecode,
    [14] = WhenDecode,
    [15] = CaseDecode,
    [16] = ResultDecode,
    [17] = DoDecode,
    [18] = LambdaDecode
};

Status ExecuteCode(Byte *code, Integer32 count, Stack *stack, Error *error) {
    for (Integer32 index = 0; index < count; index += 1) {
        Integer8 opcode = DecodeInteger8FLE(&code);
	Integer32 valueIndex = DecodeInteger32VLE(&code);
	Value *value = instruction[opcode](&code, error);
	if (value == NULL){
	    goto returnError;
        }
	StackFrameValues(stack)[valueIndex] = value;
    }
    return StatusSuccess;

returnError:
    return StatusFailure;
}
