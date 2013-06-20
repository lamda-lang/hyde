#include "module.h"

struct Module {
    Value base;
    Element value;
};

static Module *Create(Integer32 nameIndex, Error *error) {
    Module *module = MemoryAlloc(sizeof(Module), error);
    if (module == NULL) {
	goto returnError;
    }
    module->base = TypeModule;
    module->value.index = nameIndex;
    return module;

returnError:
    return NULL;
}

Value *ModuleDecode(Byte **bytes, Error *error) {
    Integer32 nameIndex = DecodeInteger32VLE(bytes);
    Module *module = Create(nameIndex, error);
    return BridgeFromModule(module);
}

void ModuleDealloc(Value *moduleValue) {
    MemoryDealloc(moduleValue);
}

void ModuleFetch(Value *moduleValue, Value **values) {
    Module *module = BridgeToModule(moduleValue);
    module->value.value = values[module->value.index];
}

Value *ModuleGetValueForIdentifier(Value *moduleValue, Value *idValue) {
    return NULL;
}

Value *ModuleEval(Value *moduleValue, bool pure, Error *error) {
    return NULL;
}
