#include "result.h"

typedef struct {
    Integer32 lamda;
    Integer8 count;
    Integer32 arg[];
} Model;

void *ResultDecode(Byte **bytes, Error *error) {
    Integer8 count = DecodeInteger8FLE(bytes);
    Model *model = MemoryAlloc(sizeof(Model) + sizeof(Integer32) * count, error);
    if (model == NULL) {
	goto returnError;
    }
    model->count = count;
    model->lamda = DecodeInteger32VLE(bytes);
    for (Integer8 index = 0; index < count; index += 1) {
	model->arg[index] = DecodeInteger32VLE(bytes);
    }
    return model;

returnError:
    return NULL;
}

Value *ResultEval(void *data, Code *code, bool pure, Error *error) {
    Model *model = data;
    Value *lamdaValue = CodeEvalInstructionAtIndex(code, model->lamda, true, error);
    if (lamdaValue == NULL) {
	goto returnError;
    }
    if (ValueType(lamdaValue) != TypeLamda) {
	*error = ErrorInvalidType;
	goto returnError;
    }
    if (StackPushFrame(GlobalStack, model->count, error) == StatusFailure) {
	goto returnError;
    }
    Value **args = StackFrameValues(GlobalStack);
    for (Integer8 index = 0; index < model->count; index += 1) {
	Value *arg = CodeEvalInstructionAtIndex(code, model->arg[index], true, error);
	if (arg == NULL) {
	    goto pullFrame;
	}
	args[index] = arg;
    }
    Value *result = LamdaResult(lamdaValue, args, model->count, error);
    if (result == NULL) {
	goto pullFrame;
    }
    StackPullFrame(GlobalStack);
    return result;

pullFrame:
    StackPullFrame(GlobalStack);
returnError:
    return NULL;
}
