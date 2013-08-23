#include "variable.h"

struct Variable {
    Type *type;
};

typedef struct {
    Integer8 variable;
} Model;

void *VariableDecode(Byte **bytes, VALUE **error) {
    Model *model = MemoryAlloc(sizeof(Model), error);
    if (model == NULL) {
        goto returnVALUE;
    }
    model->variable = DecodeInteger8FLE(bytes);
    return model;

returnVALUE:
    return NULL;
}
