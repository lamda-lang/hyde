#include "when.h"

typedef struct {
    Integer32 condition;
    Integer32 value;
} Index;

typedef struct {
    Integer8 count;
    Index index[];
} Model;

void *WhenDecode(Byte **bytes, Error *error) {
    Integer8 count = DecodeInteger8FLE(bytes);
    Model *model = MemoryAlloc(sizeof(Model) + sizeof(Index) * count, error);
    if (model == NULL) {
        goto returnError;
    }
    model->count = count;
    for (Integer8 index = 0; index < count; index += 1) {
        model->index[index].condition = DecodeInteger32VLE(bytes);
        model->index[index].value = DecodeInteger32VLE(bytes);
    }
    return model;

returnError:
    return NULL;
}

Value *WhenEval(void *data, Code *code, Value **context, bool pure, Error *error) {
    Model *model = data;
    for (Integer8 index = 0; index < model->count; index += 1) {
        Value *condition = CodeEvalInstructionAtIndex(code, context, model->index[index].condition, true, error);
        if (condition == NULL) {
            goto returnError;
        }
        if (condition == BooleanTrueSingleton()) {
            return CodeEvalInstructionAtIndex(code, context, model->index[index].value, pure, error);
        }
    }
    return NilSingleton();

returnError:
    return NULL;
}
