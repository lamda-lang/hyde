#include "variable.h"

typedef struct {
    Integer8 variable;
} Model;

void *VariableDecode(Byte **bytes, Error *error) {
    Model *model = MemoryAlloc(sizeof(Model), error);
    if (model == NULL) {
        goto returnError;
    }
    model->variable = DecodeInteger8FLE(bytes);
    return model;

returnError:
    return NULL;
}

Value *VariableEval(void *data, Code *code, Value **context, Bool pure, Error *error) {
    Model *model = data;
    return context[model->variable];
}
