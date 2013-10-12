#include "identifier.h"

typedef struct {
    Integer8 length;
    Integer8 codepoints[];
} Component;

struct Identifier {
    Integer8 count;
    Component *components[];
};

static Component *IdentifierCreateComponent(Integer32 length) {
    Component *component = MemoryAllocRegion(sizeof(Component), sizeof(Integer8), length);
    component->length = length;
    return component;
}

static Identifier *IdentifierCreate(Integer32 count) {
    Identifier *id = MemoryAllocRegion(sizeof(Identifier), sizeof(Component *), count);
    id->count = count;
    return id;
}

static void IdentifierDeallocComponent(Component *component) {
    MemoryDealloc(component);
}

static void IdentifierDealloc(Identifier *id, Integer32 count) {
    for (Integer8 index = 0; index < count; index += 1)
        IdentifierDeallocComponent(id->components[index]);
    MemoryDealloc(id);
}

static Component *IdentifierDecodeComponent(Binary *binary, Integer32 *offset) {
    Integer8 length;
    if (!BinaryDecodeInteger8(binary, offset, &length))
        return NULL;
    Component *component = IdentifierCreateComponent(length);
    for (Integer8 index = 0; index < length; index += 1)
        if (!BinaryDecodeInteger8(binary, offset, component->codepoints + index))
            goto out;
    return component;

out:
    IdentifierDeallocComponent(component);
    return NULL;
}

Value *IdentifierDecodePrimitive(Binary *binary, Integer32 *offset) {
    Integer8 count;
    if (!BinaryDecodeInteger8(binary, offset, &count))
        return NULL;
    Identifier *id = IdentifierCreate(count);
    Integer8 index = 0;
    while (index < count) {
        Component *component = IdentifierDecodeComponent(binary, offset);
        if (component == NULL)
            goto out;
        index += 1;
    }
    return ValueCreateIdentifier(id);

out:
    IdentifierDealloc(id, index);
    return NULL;
}
