#include <builtin/module.h>

/* type */
typedef struct Module Module;
typedef struct Definition Definition;
typedef struct Scope Scope;
typedef struct Import Import;

struct Module {
    VALUE *type;
    Scope *scope;
    Integer32 count;
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

struct Import {
    VALUE *pathValue;
    VALUE *variableValue;
};

/* private */
static Module *ModuleCreate(Scope *scope, Error *error) {
    Module *module = MemoryAlloc(sizeof(Module), error);
    if (*error != ErrorNone) return NULL;
    module->type = RuntimeValueForConstant(ConstantModuleType);
    module->scope = scope;
    return module;
}

static Scope *ModuleCreateScope(Integer32 count, Error *error) {
    Scope *scope = MemoryAlloc(sizeof(Scope) + sizeof(Definition) * count, error);
    if (*error != ErrorNone) return NULL;
    scope->count = count;
    return scope;
}

static void ModuleDeallocScope(Scope *scope) {
    MemoryDealloc(scope);
}

static Scope *ModuleDecodeScope(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32(bytes);
    Scope *scope = ModuleCreateScope(count, error);
    if (*error != ErrorNone) goto returnError;
    for (Integer32 index = 0; index < count; index += 1) {
        scope->definitions[index].variable = DecodeValue(bytes, error);
        if (*error != ErrorNone) goto deallocScope;
        scope->definitions[index].value = DecodeValue(bytes, error);
        if (*error != ErrorNone) goto deallocScope;
        scope->definitions[index].local = ModuleDecodeScope(bytes, error);
        if (*error != ErrorNone) goto deallocScope;
    }
    return scope;

deallocScope:
    ModuleDeallocScope(scope);
returnError:
    return NULL;
}

/* public */
VALUE *ModuleDecode(Byte **bytes, Error *error) {
    Scope *scope = ModuleDecodeScope(bytes, error);
    if (*error != ErrorNone) goto returnError;
    Module *module = ModuleCreate(scope, error);
    if (*error != ErrorNone) goto deallocScope;
    return module;

deallocScope:
    ModuleDeallocScope(scope);
returnError:
    return NULL;
}
