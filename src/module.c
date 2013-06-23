#include "module.h"

struct Module {
    Value base;
};

static Module *Create(Error *error) {
    Module *module = MemoryAlloc(sizeof(Module), error);
    if (module == NULL) {
	goto returnError;
    }
    module->base = TypeModule;
    return module;

returnError:
    return NULL;
}

void ModuleDealloc(Value *moduleValue) {
    MemoryDealloc(moduleValue);
}

Value *ModuleGetValueForIdentifier(Value *moduleValue, Value *idValue) {
    return NULL;
}
