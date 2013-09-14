#include <builtin/module.h>

typedef struct Definition Definition;
typedef struct Scope Scope;
typedef struct Dependency Dependency;

struct Dependency {
    int foo;
};

struct Module {
    Scope *scope;
    Integer32 count;
    Dependency dependencies[];
};

struct Definition {
    Value *name;
    Value *value;
    Scope *local;
};

struct Scope {
    Integer32 count;
    Definition definitions[];
};

static Module *ModuleCreate(Scope *scope, Integer32 count) {
    Module *module = MemoryAlloc(sizeof(Module) + sizeof(Dependency) * count);
    if (module == NULL)
        return NULL;
    module->scope = scope;
    module->count = count;
    return module;
}

static Scope *ModuleCreateScope(Integer32 count) {
    Scope *scope = MemoryAlloc(sizeof(Scope) + sizeof(Definition) * count);
    if (scope == NULL)
        return NULL;
    scope->count = count;
    return scope;
}

static Scope *ModuleDecodeScope(Byte **bytes, Error *error) {
    return NULL;
}

Value *ModuleDecode(Byte **bytes) {
    return NULL;
}

Value *ModuleEval(Module *module, Value *context) {
}

Bool ModuleEqual(Module *module, Module *other){
    return TRUE;
}

Size ModuleRelease(Module *module) {
}
