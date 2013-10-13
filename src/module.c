#include "module.h"

typedef struct {
    Value *name;
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

static Module *ModuleDecodePrimitive(Binary *binary, Integer32 *offset) {
    Integer32 count;
    if (!BinaryDecodeInteger32(binary, offset, &count))
        return NULL;
    Module *module = ModuleCreate(count);
    Integer32 index = 0;
    while (index < count) {
        Value *name = BinaryDecodeValue(binary, offset);
        if (name == NULL)
            goto out;
        Value *value = BinaryDecodeValue(binary, offset);
        if (value == NULL)
            goto out;
        Module *local = ModuleDecodePrimitive(binary, offset);
        if (module == NULL)
            goto out;
        module->definitions[index].name = name;
        module->definitions[index].value = value;
        module->definitions[index].local = local;
        index += 1;
    }
    return module;

out:
    ModuleDealloc(module, index);
    return NULL;
}

Value *ModuleDecode(Binary *binary, Integer32 *offset) {
    Module *module = ModuleDecodePrimitive(binary, offset);
    return ValueCreateModule(module);
}
