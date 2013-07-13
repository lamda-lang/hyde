#include "import.h"

typedef struct {
    Integer32 name;
} Model;

void *ImportDecode(Byte **bytes, Error *error) {
    Model *model = MemoryAlloc(sizeof(Model), error);
    if (model == NULL) {
        goto returnError;
    }
    model->name = DecodeInteger32VLE(bytes);
    return model;

returnError:
    return NULL;
}

Value *ImportEval(void *data, Code *code, Value **context, Bool pure, Error *error) {
    Model *model = data;
    Value *stringValue = CodeEvalInstructionAtIndex(code, context, model->name, TRUE, error);
    if (stringValue == NULL) {
        goto returnError;
    }
    return MapGetValueForKey(NULL, stringValue); /* missing */

returnError:
    return NULL;
}
