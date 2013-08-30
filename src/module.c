#include "module.h"

typedef struct {
    VALUE *type;
} Module;

static Module *ModuleCreate(Error *error) {
    Module *module = MemoryAlloc(sizeof(Module), error);
    return module;
}

VALUE *ModuleDecode(Byte **bytes, Error *error) {
    Module *module = ModuleCreate(error);
    return module;
}
