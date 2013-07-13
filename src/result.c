#include "result.h"

typedef struct {
    Integer32 lamda;
    Integer8 arity;
    Integer32 arg[];
} Model;

void *ResultDecode(Byte **bytes, Error *error) {
    Integer8 arity = DecodeInteger8FLE(bytes);
    Model *model = MemoryAlloc(sizeof(Model) + sizeof(Integer32) * arity, error);
    if (model == NULL) {
        goto returnError;
    }
    model->arity = arity;
    model->lamda = DecodeInteger32VLE(bytes);
    for (Integer8 index = 0; index < arity; index += 1) {
        model->arg[index] = DecodeInteger32VLE(bytes);
    }
    return model;

returnError:
    return NULL;
}

Value *ResultEval(void *data, Code *code, Value **context, Bool pure, Error *error) {
    Model *model = data;
    Value *lamdaValue = CodeEvalInstructionAtIndex(code, context, model->lamda, TRUE, error);
    if (lamdaValue == NULL) {
        goto returnError;
    }
    if (ValueType(lamdaValue) != TypeLamda) {
        ErrorSet(error, ErrorInvalidType);
        goto returnError;
    }
    if (LamdaArity(lamdaValue) != model->arity) {
        ErrorSet(error, ErrorArityMismatch);
        goto returnError;
    }
    Value **args = LamdaCreateContext(lamdaValue, error);
    for (Integer8 index = 0; index < model->arity; index += 1) {
        Value *value = CodeEvalInstructionAtIndex(code, args, model->arg[index], TRUE, error);
        if (value == NULL) {
            goto deallocContext;
        }
        context[index] = value;
    }
    Value *result = LamdaResult(lamdaValue, context, error);
    LamdaDeallocContext(context);
    return result;

deallocContext:
    LamdaDeallocContext(context);
returnError:
    return NULL;
}
