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

static Module *ModuleDecode(Binary *binary, Integer32 *offset);

static void ModuleDealloc(Module *module, Integer32 count) {
    for (Integer32 index = 0; index < count; index += 1) {
        Module *local = module->definitions[index].local;
        ModuleDealloc(local, local->count);
    }
    MemoryDealloc(module);
}

static Module *ModuleCreate(Integer32 count) {
    Module *module = MemoryAllocRegion(sizeof(Module), sizeof(Definition), count);
    module->count = count;
    return module;
}

static Definition *ModuleCreateDefinition(Value *name, Value *value, Module *local) {
    Definition *definition = MemoryAllocUnit(sizeof(Definition));
    definition->name = name;
    definition->value = value;
    definition->local = local;
    return definition;
}

static Definition *ModuleDecodeDefinition(Binary *binary, Integer32 *offset) {
    Value *name = BinaryDecodeValue(binary, offset);
    if (name == NULL)
        return NULL;
    Value *value = BinaryDecodeValue(binary, offset);
    if (value == NULL)
        return NULL;
    Module *module = ModuleDecode(binary, offset);
    if (module == NULL)
        return NULL;
    Definition *definition = ModuleCreateDefinition(name, value, module);
    if (definition == NULL)
        goto out;
    return definition;

out:
    ModuleDealloc(module, module->count);
    return NULL;
}

static Module *ModuleDecode(Binary *binary, Integer32 *offset) {
    /*
    Integer32 count;
    if (!BinaryDecodeInteger32(binary, offset, &count))
        return NULL;
    Module *module = ModuleCreate(count);
    Integer32 index = 0;
    while (index < count) {
        Definition *definition = ModuleDecodeDefinition(binary, offset);
        if (definition == NULL)
            goto out;
        module->definitions[index] = definition;
        index += 1;
    }
    return module;

out:
    ModuleDealloc(module, index);
   */ return NULL;
}

Value *ModuleDecodePrimitive(Binary *binary, Integer32 *offset) {
    Module *module = ModuleDecode(binary, offset);
    return ValueCreateModule(module);
}
