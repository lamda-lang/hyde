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
    [16] = LamdaDecode
};

Value *ExecuteCode(Byte *bytes, Value **args, Integer8 argCount, Value **context, Integer8 contextLength, Error *error) {
    Integer32 valueCount = DecodeInteger32VLE(&bytes);
    if (StackPushFrame(valueCount, error) == StatusFailure) {
	goto returnError;
    }
    Value **values = StackFrameValues();
    Value **argHead = values + 1;
    Value **contextHead = argHead + argCount; 
    MemoryCopy(args, argHead, sizeof(Value *) * argCount);
    MemoryCopy(context, contextHead, sizeof(Value *) * contextLength);
    for (Integer32 index = 0; index < valueCount; index += 1) {
        Integer8 opcode = DecodeInteger8FLE(&bytes);
	Integer32 valueIndex = DecodeInteger32VLE(&bytes);
	Value *value = instruction[opcode](&bytes, error);
	if (value == NULL) {
	    goto pullFrame;
	}
	values[valueIndex] = value;
    }
    for (Integer32 index = 0; index < valueCount; index += 1) {
	ValueFetch(values[index], values);
    }
    Value *result = values[0];
    StackPullFrame();
    return result;

pullFrame:
    StackPullFrame();
returnError:
    return NULL;
}
