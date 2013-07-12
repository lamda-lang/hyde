#include "module.h"

typedef struct {
    Value *id;
    Value *value;
} Pair;

typedef struct {
    Integer32 id;
    Integer32 value;
} Index;

typedef struct {
    Integer32 count;
    Index pair[];
} Model;

struct Module {
    Value base;
    Integer32 count;
    Pair pair[];
};

static Module *Create(Integer32 count, Error *error) {
    Module *module = MemoryAlloc(sizeof(Module) + sizeof(Pair) * count, error);
    if (module == NULL) {
        goto returnError;
    }
    module->base = TypeModule;
    module->count = count;
    return module;

returnError:
    return NULL;
}

Value *ModuleCreate(Integer32 count, Error *error) {
    Module *module = Create(count, error);
    return BridgeFromModule(module);
}

void *ModuleDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32VLE(bytes);
    Model *model = MemoryAlloc(sizeof(Model) + sizeof(Index) * count, error);
    if (model == NULL) {
        goto returnError;
    }
    model->count = count;
    for (Integer32 index = 0; index < count; index += 1) {
        model->pair[index].id = DecodeInteger32VLE(bytes);
        model->pair[index].value = DecodeInteger32VLE(bytes);
    }
    return model;

returnError:
    return NULL;
}

Value *ModuleEval(void *data, Code *code, Value **context, bool pure, Error *error) {
    Model *model = data;
    Module *module = Create(model->count, error);
    if (module == NULL) {
        goto returnError;
    }
    Value *moduleValue = BridgeFromModule(module);
    for (Integer32 index = 0; index < model->count; index += 1) {
        Value *key = CodeEvalInstructionAtIndex(code, context, model->pair[index].id, true, error);
        if (key == NULL) {
            goto deallocModule;
        }
        Value *value = CodeEvalInstructionAtIndex(code, context, model->pair[index].value, true, error);
        if (value == NULL) {
            goto deallocModule;
        }
        module->pair[index].id = key;
        module->pair[index].value = value;
    }
    return moduleValue;

deallocModule:
    ModuleDealloc(moduleValue);
returnError:
    return NULL;
}

void ModuleDealloc(Value *moduleValue) {
    MemoryDealloc(moduleValue);
}

Value *ModuleGetValueForIdentifier(Value *moduleValue, Value *idValue) {
    Module *module = BridgeToModule(moduleValue);
    for (Integer32 index = 0; index < module->count; index += 1) {
        if (ValueEqual(module->pair[index].id, idValue)) {
            return module->pair[index].value;
        }
    }
    return NULL;
}
