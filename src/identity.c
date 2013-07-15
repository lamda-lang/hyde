#include "identity.h"

typedef struct {
    Integer8 identity;
} Model;

void *IdentityDecode(Byte **bytes, Error *error) {
    Model *model = MemoryAlloc(sizeof(Model), error);
    if (model == NULL) {
        goto returnError;
    }
    model->identity = DecodeInteger8FLE(bytes);
    return model;

returnError:
    return NULL;
}

Value *IdentityEval(void *data, Code *code, Value **context, Bool pure, Error *error) {
    Model *model = data;
    return context[model->identity];
}
