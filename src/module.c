#include "module.h"

typedef struct {
    Identifier *name;
    Value *value;
    Module *local;
} Definition;

struct Module {
    Integer32 count;
    Definition definitions[];
};

static Module *ModuleCreate(Integer32 count) {
    Module *module = MemoryAllocRegion(sizeof(Module), sizeof(Definition), count);
    module->count = count;
    return module;
}

static void ModuleDealloc(Module *module, Integer32 count) {
    for (Integer32 index = 0; index < count; index += 1) {
        Module *local = module->definitions[index].local;
        ModuleDealloc(local, local->count);
    }
    MemoryDealloc(module);
}

static Bool ModuleDecodePrimitive(Binary *binary, Integer32 *offset, Module **module) {
    Integer32 count;
    if (!BinaryDecodeInteger32(binary, offset, &count))
        return FALSE;
    *module = ModuleCreate(count);
    Integer32 index = 0;
    while (index < count) {
        Identifier *name;
        Value *value;
        Module *local;
        if (!IdentifierDecodePrimitive(binary, offset, &name))
            goto out;
        if (!BinaryDecodeValue(binary, offset, &value))
            goto out;
        if (!ModuleDecodePrimitive(binary, offset, &local))
            goto out;
        (*module)->definitions[index].name = name;
        (*module)->definitions[index].value = value;
        (*module)->definitions[index].local = local;
        index += 1;
    }
    return TRUE;

out:
    ModuleDealloc(*module, index);
    return FALSE;
}

Bool ModuleDecode(Binary *binary, Integer32 *offset, Value **value) {
    Module *module;
    if (!ModuleDecodePrimitive(binary, offset, &module))
        return FALSE;
    *value = ValueCreateModule(module);
    return TRUE;
}
