#include <builtin/identifier.h>

typedef struct Identifier Identifier;
typedef struct Component Component;

struct Identifier {
    Value value;
    Integer8 count;
    Component *components[];
};

struct Component {
    Integer8 length;
    Integer8 codepoint[];
};

static Identifier *IdentifierCreate(Integer8 count, Error *error) {
    Identifier *id = MemoryAlloc(sizeof(Identifier) + sizeof(Integer8) * count, error);
    if (*error != ErrorNone) return NULL;
    id->value = ValueIdentifier;
    id->count = count;
    return id;
}

static Component *IdentifierComponentCreate(Integer8 length, Error *error) {
    Component *component = MemoryAlloc(sizeof(Component) + sizeof(Integer8) * length, error);
    if (*error != ErrorNone) return NULL;
    component->length = length;
    return component;
}

static Identifier *IdentifierDealloc(Identifier *id, Integer8 count) {
    for (Integer8 index = 0; index < count; index += 1) MemoryDealloc(id->components[index]);
    MemoryDealloc(id);
    return NULL;
}

Value *IdentifierDecode(Byte **bytes, Error *error) {
    Integer8 count = DecodeInteger8(bytes);
    Identifier *id = IdentifierCreate(count, error);
    if (*error != ErrorNone) return IdentifierDealloc(id, 0);;
    for (Integer8 index = 0; index < count; index += 1) {
        Integer8 length = DecodeInteger8(bytes);
        Component *component = IdentifierComponentCreate(length, error);
        if (*error != ErrorNone) return IdentifierDealloc(id, index);
        for (Integer8 index = 0; index < length; index += 1) component->codepoint[index] = DecodeInteger8(bytes);
        id->components[index] = component;
    }
    return id;
}

Bool IdentifierEqual(Value *idValue, Value *otherValue) {
    if (idValue == otherValue) return TRUE;
    Identifier *id = idValue;
    Identifier *other = otherValue;
    if (id->count != other->count) return FALSE;
    for (Integer8 index = 0; index < id->count; index += 1) {
        if (id->components[index]->length != other->components[index]->length) return FALSE;
        if (!MemoryEqual(id->components[index]->codepoint, other->components[index]->codepoint, sizeof(Integer8) * id->components[index]->length)) return FALSE;
    }
    return TRUE;
}

void IdentifierRelease(Value *idValue) {
    Identifier *id = idValue;
    IdentifierDealloc(id, id->count);
}
