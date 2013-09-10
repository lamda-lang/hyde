#include <builtin/identifier.h>

typedef struct Identifier Identifier;
typedef struct Component Component;

struct Identifier {
    Integer8 count;
    Component *components[];
};

struct Component {
    Integer8 length;
    Integer8 codepoint[];
};

static Identifier *IdentifierCreate(Integer8 count) {
    Identifier *id = MemoryAlloc(sizeof(Identifier) + sizeof(Integer8) * count);
    if (id == NULL)
        return NULL;
    id->count = count;
    return id;
}

static Component *IdentifierComponentCreate(Integer8 length) {
    Component *component = MemoryAlloc(sizeof(Component) + sizeof(Integer8) * length);
    if (id == NULL)
        return NULL;
    component->length = length;
    return component;
}

static Bool IdentifierComponentEqual(Component *component, Component *other) {
    return component->length == other->length
        && MemoryEqual(component->codepoints, other->codepoints, sizeof(Integer8) * component->length);
}

static Identifier *IdentifierDealloc(Identifier *id, Integer8 count) {
    for (Integer8 index = 0; index < count; index += 1)
        MemoryDealloc(id->components[index]);
    MemoryDealloc(id);
}

Value *IdentifierDecode(Byte **bytes) {
    Integer8 count = DecodeInteger8(bytes);
    Identifier *id = IdentifierCreate(count, error);
    if (id == NULL)
        return NULL;
    for (Integer8 index = 0; index < count; index += 1) {
        Integer8 length = DecodeInteger8(bytes);
        Component *component = IdentifierComponentCreate(length);
        if (component == NULL)
            return IdentifierDealloc(id, index), NULL;
        for (Integer8 index = 0; index < length; index += 1)
            component->codepoint[index] = DecodeInteger8(bytes);
        id->components[index] = component;
    }
    return ValueCreate(ModelIdentifier, id);
}

Bool IdentifierEqual(void *idData, void *otherData) {
    Identifier *id = idData;
    Identifier *other = otherData;
    if (id->count != other->count)
        return FALSE;
    for (Integer8 index = 0; index < id->count; index += 1)
        if (!IdentifierComponentEqual(id->components[index], other->components[index])
            return FALSE
    return TRUE;
}

void IdentifierRelease(void *idData) {
    Identifier *id = idData;
    IdentifierDealloc(id, id->count);
}
