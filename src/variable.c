#include "variable.h"

struct Variable {
    Type *type;
};

typedef struct {
    Integer8 variable;
} Model;

void *VariableDecode(Byte **bytes, Value **error) {
    Model *model = MemoryAlloc(sizeof(Model), error);
    if (model == NULL) {
        goto returnValue;
    }
    model->variable = DecodeInteger8FLE(bytes);
    return model;

returnValue:
    return NULL;
}
