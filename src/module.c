#include "module.h"

typedef struct {
    VALUE *type;
} Module;

static Module *ModuleCreate(VALUE **error) {
    Module *module = MemoryAlloc(sizeof(Module), error);
    return module;
}

VALUE *ModuleDecode(Byte **bytes, VALUE **error) {
    Module *module = ModuleCreate(error);
    return module;
}
