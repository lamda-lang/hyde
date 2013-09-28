#include "module.h"

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

static Size ModuleSizeOf(Integer32 count) {
    return sizeof(Module) + sizeof(Definition) * count;
}

static Module *ModuleCreate(Integer32 count, Error *error) {
    Size size = ModuleSizeOf(count);
    Module *module = MemoryAlloc(size, error);
    if (ERROR(error))
        return NULL;
    module->count = count;
    return module;
}

static Size ModuleDealloc(Module *module, Integer32 count) {
    Size size = ModuleSizeOf(module->count);
    for (Integer32 index = 0; index < count; index += 1)
        size += ModuleRelease(module->definitions[index].local);
    MemoryDealloc(module);
    return size;
}

Size ModuleSize(Module *module) {
    Size size = INTEGER_32_SIZE;
    for (Integer32 index = 0; index < module->count; index += 1)
        size += ModuleSize(module->definitions[index].local);
    return size;
}

Size ModuleEncode(Module *module, Byte **bytes) {
    EncodeInteger32(module->count, bytes);
    for (Integer32 index = 0; index < module->count; index += 1) {
        ValueEncode(module->definitions[index].name, bytes);
        ValueEncode(module->definitions[index].value, bytes);
        ModuleEncode(module->definitions[index].local, bytes);
    }
    return ModuleSize(module);
}

Module *ModuleDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32(bytes);
    Module *module = ModuleCreate(count, error);
    if (ERROR(error))
        return NULL;
    Integer32 index = 0;
    while (index < count) {
        module->definitions[index].name = ValueDecode(bytes, error);
        if (ERROR(error))
            goto module;
        module->definitions[index].value = ValueDecode(bytes, error);
        if (ERROR(error))
            goto module;
        module->definitions[index].local = ModuleDecode(bytes, error);
        if (ERROR(error))
            goto module;
        index += 1;
    }
    return module;

module:
    ModuleDealloc(module, index);
    return NULL;
}

/* incomplete */
Value *ModuleEval(Value *value, Module *module, Value *context, Error *error) {
    for (Integer32 index = 0; index < module->count; index += 1) {
        context = ValueSetValueForKey(context, module->definitions[index].value, module->definitions[index].name, error);
        if (ERROR(error))
            return NULL;
    }
    Module *new = ModuleCreate(module->count, error);
    if (ERROR(error))
        return NULL;
    for (Integer32 index = 0; index < module->count; index += 1) {
        new->definitions[index].name = module->definitions[index].name;
        new->definitions[index].value = ValueEval(module->definitions[index].value, context, error);
        if (ERROR(error))
            goto new;
    }
    return ValueCopy(new, error);

new:
    ModuleRelease(module);
    return NULL;
}

/* missing */
Bool ModuleEqual(Module *module, Module *other) {
    return TRUE;
}

Size ModuleRelease(Module *module) {
    return ModuleDealloc(module, module->count);
}
