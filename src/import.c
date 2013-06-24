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

Value *ModuleEval(void *data, Code *code, bool pure, Error *error) {
    Model *model = data;
    Value *stringValue = CodeEvalInstructionAtIndex(code, model->name, true, error);
    if (stringValue == NULL) {
	goto returnError;
    }
    return MapGetValueForKey(GlobalModuleMap, stringValue);

returnError:
    return NULL;
}
