#include <builtin/module.h>

typedef struct Definition Definition;

struct Definition {
    Value *name;
    Value *value;
    Module *local;
};

struct Module {
    Integer32 count;
    Definition definitions[];
};

static Size ModuleSize(Integer32 count) {
    return sizeof(Module) + sizeof(Definition) * count;
}

static Module *ModuleCreate(Integer32 count) {
    Size size = ModuleSize(count);
    Module *module = MemoryAlloc(size);
    if (module == NULL)
        return NULL;
    module->count = count;
    return module;
}

static Size ModuleDealloc(Module *module, Integer32 count) {
    Size size = ModuleSize(module->count);
    for (Integer32 index = 0; index < count; index += 1)
        size += ModuleRelease(module->definitions[index].local);
    MemoryDealloc(module);
    return size;
}

static Module *ModuleDecodeRecursive(Byte **bytes) {
    Integer32 count = DecodeInteger32(bytes);
    Module *module = ModuleCreate(count);
    if (module == NULL)
        return NULL;
    for (Integer32 index = 0; index < count; index += 1) {
        Value *name = ValueDecode(bytes);
        if (name == NULL)
            return ModuleDealloc(module, index), NULL;
        Value *value = ValueDecode(bytes);
        if (value == NULL)
            return ModuleDealloc(module, index), NULL;
        Module *local = ModuleDecodeRecursive(bytes);
        if (local == NULL)
            return ModuleDealloc(module, index), NULL;
        module->definitions[index].name = name;
        module->definitions[index].value = value;
        module->definitions[index].local = local;
    }
    return module;
}

Value *ModuleDecode(Byte **bytes) {
    Module *module = ModuleDecodeRecursive(bytes);
    return ValueCreate(MODEL_MODULE, module);
}

Value *ModuleEval(Module *module, Value *context) {
    for (Integer32 index = 0; index < module->count; index += 1) {
        context = ValueSetValueForKey(context, module->definitions[index].value, module->definitions[index].name);
        if (context == NULL)
            return NULL;
    }
    Module *new = ModuleCreate(module->count);
    if (new == NULL)
        return NULL;
    for (Integer32 index = 0; index < module->count; index += 1) {
        Value *value = ValueEval(module->definitions[index].value, context);
        if (value == NULL)
            return /**/ NULL;
        new->definitions[index].name = module->definitions[index].name;
        new->definitions[index].value = value;
    }
    return ValueCreate(MODEL_MODULE, new);
}

Value *ModuleEqual(Module *module, Module *other) {
}

Size ModuleRelease(Module *module) {
    return ModuleDealloc(module, module->count);
}
