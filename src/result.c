#include "result.h"

struct Result {
    Type *type;
};

typedef struct {
    Integer32 lamda;
    Integer8 arity;
    Integer32 arg[];
} Model;

void *ResultDecode(Byte **bytes, Value **error) {
    Integer8 arity = DecodeInteger8FLE(bytes);
    Model *model = MemoryAlloc(sizeof(Model) + sizeof(Integer32) * arity, error);
    if (model == NULL) {
        goto returnValue;
    }
    model->arity = arity;
    model->lamda = DecodeInteger32VLE(bytes);
    for (Integer8 index = 0; index < arity; index += 1) {
        model->arg[index] = DecodeInteger32VLE(bytes);
    }
    return model;

returnValue:
    return NULL;
}
