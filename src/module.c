#include "module.h"

struct Module {
    Value base;
    Element name;
};

static Module *Create(Integer32 nameIndex, Error *error) {
    Module *module = MemoryAlloc(sizeof(Module), error);
    if (module == NULL) {
	goto returnError;
    }
    module->base = TypeModule;
    module->name.index = nameIndex;
    return module;

returnError:
    return NULL;
}

Value *ModuleValueBridge(Module *module) {
    return (Value *)module;
}

Value *ModuleDecode(Byte **bytes, Error *error) {
    Integer32 nameIndex = DecodeInteger32VLE(bytes);
    Module *module = Create(nameIndex, error);
    return ModuleValueBridge(module);
}

void ModuleDealloc(Value *moduleValue) {
    MemoryDealloc(moduleValue);
}

void ModuleFetch(Value *moduleValue, Value **values) {
    Module *module = ValueModuleBridge(moduleValue);
    module->name.value = values[module->name.index];
}

Value *ModuleGetValueForIdentifier(Module *module, Identifier *id) {
}

Value *ModuleEval(Value *moduleValue, bool pure, Error *error) {
    return NULL;
}

Module *ModuleWithID(Char *path) {
}

Status ModuleLoad(Char *path, Error *error) {
}
