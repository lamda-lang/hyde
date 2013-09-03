#include "module.h"

typedef struct {
    VALUE *type;
} Module;

static Module *ModuleCreate(Error *error) {
    Module *module = MemoryAlloc(sizeof(Module), error);
    if (*error != ErrorNone) return NULL;
    module->type = RuntimeValueForConstant(ConstantModuleType);
    return module;
}

VALUE *ModuleDecode(Byte **bytes, Error *error) {
    Module *module = ModuleCreate(error);
    return module;
}
