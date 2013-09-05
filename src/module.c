#include "module.h"

/* type */
typedef struct Module Module;
typedef struct Definition Definition;
typedef struct Scope Scope;

struct Module {
    VALUE *type;
    Scope *root;
};

struct Definition {
    VALUE *variable;
    VALUE *value;
    Scope *local;
};

struct Scope {
    Integer32 count;
    Definition definitions[];
};

/* private */
static Module *ModuleCreate(Error *error) {
    Module *module = MemoryAlloc(sizeof(Module), error);
    if (*error != ErrorNone) return NULL;
    module->type = RuntimeValueForConstant(ConstantModuleType);
    return module;
}

/* public */
VALUE *ModuleDecode(Byte **bytes, Error *error) {
    Module *module = ModuleCreate(error);
    return module;
}
