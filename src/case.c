#include "case.h"

struct Case {
    Type *type;
};

typedef struct {
    Integer32 match;
    Integer32 guard;
    Integer32 value;
} Clause;

typedef struct {
    Integer8 length;
    Integer32 arg;
    Clause clause[];
} Model;

void *CaseDecode(Byte **bytes, Value **error) {
    Integer8 length = DecodeInteger8FLE(bytes);
    Model *model = MemoryAlloc(sizeof(Model) + sizeof(Clause) * length, error);
    if (model == NULL) {
        goto returnValue;
    }
    model->length = length;
    model->arg = DecodeInteger32VLE(bytes);
    for (Integer8 index = 0; index < length; index += 1) {
        model->clause[index].match = DecodeInteger32VLE(bytes);
        model->clause[index].guard = DecodeInteger32VLE(bytes);
        model->clause[index].value = DecodeInteger32VLE(bytes);
    }
    return model;

returnValue:
    return NULL;
}
