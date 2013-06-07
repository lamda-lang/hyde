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
    [11] = LambdaDecode,
    [12] = DoDecode,
    [13] = ResultDecode
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
