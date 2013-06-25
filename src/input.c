#include "input.h"

typedef struct {
    Integer8 input;
} Model;

void *InputDecode(Byte **bytes, Error *error) {
    Model *model = MemoryAlloc(sizeof(Model), error);
    if (model == NULL) {
	goto returnError;
    }
    model->input = DecodeInteger8FLE(bytes);
    return model;

returnError:
    return NULL;
}

Value *InputEval(void *data, Code *code, bool pure, Error *error) {
    Model *model = data;
    return StackFrameValues(GlobalStack)[model->input];
}
