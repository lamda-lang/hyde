#include "when.h"

struct When {
    Type *type;
};

typedef struct {
    Integer32 condition;
    Integer32 value;
} Index;

typedef struct {
    Integer8 count;
    Index index[];
} Model;

void *WhenDecode(Byte **bytes, VALUE **error) {
    Integer8 count = DecodeInteger8FLE(bytes);
    Model *model = MemoryAlloc(sizeof(Model) + sizeof(Index) * count, error);
    if (model == NULL) {
        goto returnVALUE;
    }
    model->count = count;
    for (Integer8 index = 0; index < count; index += 1) {
        model->index[index].condition = DecodeInteger32VLE(bytes);
        model->index[index].value = DecodeInteger32VLE(bytes);
    }
    return model;

returnVALUE:
    return NULL;
}
