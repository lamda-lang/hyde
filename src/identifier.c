#include "identifier.h"

typedef struct Component Component;

struct Identifier {
    Integer8 count;
    Component *components[];
};

struct Component {
    Integer8 length;
    Integer8 codepoints[];
};

static Size IdentifierSize(Integer8 count) {
    return sizeof(Identifier) + sizeof(Integer8) * count;
}

static Size IdentifierComponentSize(Integer8 length) {
    return sizeof(Component) + sizeof(Integer8) * length;
}

static Identifier *IdentifierCreate(Integer8 count, Error *error) {
    Size size = IdentifierSize(count);
    Identifier *id = MemoryAlloc(size, error);
    if (ERROR(error))
        return NULL;
    id->count = count;
    return id;
}

static Component *IdentifierComponentCreate(Integer8 length, Error *error) {
    Size size = IdentifierComponentSize(length);
    Component *component = MemoryAlloc(size, error);
    if (ERROR(error))
        return NULL;
    component->length = length;
    return component;
}

static Bool IdentifierComponentEqual(Component *component, Component *other) {
    return component->length == other->length
        && MemoryEqual(component->codepoints, other->codepoints, sizeof(Integer8) * component->length);
}

static void IdentifierDealloc(Identifier *id, Integer8 count) {
    for (Integer8 index = 0; index < count; index += 1)
        MemoryDealloc(id->components[index]);
    MemoryDealloc(id);
}

Identifier *IdentifierDecode(Byte **bytes, Error *error) {
    Integer8 count = DecodeInteger8(bytes);
    Identifier *id = IdentifierCreate(count, error);
    if (ERROR(error))
        return NULL;
    Integer8 index = 0;
    while (index < count) {
        Integer8 length = DecodeInteger8(bytes);
        Component *component = IdentifierComponentCreate(length, error);
        if (ERROR(error))
            goto id;
        for (Integer8 index = 0; index < length; index += 1)
            component->codepoints[index] = DecodeInteger8(bytes);
        id->components[index] = component;
        index += 1;
    }
    return id;

id:
    IdentifierDealloc(id, index);
    return NULL;
}

Bool IdentifierEqual(Identifier *id, Identifier *other) {
    if (id->count != other->count)
        return FALSE;
    for (Integer8 index = 0; index < id->count; index += 1)
        if (!IdentifierComponentEqual(id->components[index], other->components[index]))
            return FALSE;
    return TRUE;
}

Size IdentifierRelease(Identifier *id) {
    Size size = IdentifierSize(id->count);
    for (Integer8 index = 0; index < id->count; index += 1)
        size += IdentifierComponentSize(id->components[index]->length);
    IdentifierDealloc(id, id->count);
    return size;
}
