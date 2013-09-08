#include <builtin/identifier.h>

typedef struct Identifier Identifier;
typedef struct Component Component;

struct Identifier {
    VALUE *type;
    Integer8 count;
    Component *components[];
};

struct Component {
    Integer8 length;
    Integer8 codepoint[];
};

static Identifier *IdentifierCreate(Integer8 count, Error *error) {
    Identifier *identifier = MemoryAlloc(sizeof(Identifier) + sizeof(Integer8) * count, error);
    if (*error != ErrorNone) return NULL;
    identifier->type = NULL;
    identifier->count = count;
    return identifier;
}

static Component *IdentifierComponentCreate(Integer8 length, Error *error) {
    Component *component = MemoryAlloc(sizeof(Component) + sizeof(Integer8) * length, error);
    if (*error != ErrorNone) return NULL;
    component->length = length;
    return component;
}

static void IdentifierRemove(Identifier *identifier, Integer8 count) {
    for (Integer8 index = 0; index < count; index += 1) MemoryDealloc(identifier->components[index]);
    MemoryDealloc(identifier);
}

VALUE *IdentifierDecode(Byte **bytes, Error *error) {
    Integer8 count = DecodeInteger8(bytes);
    Identifier *identifier = IdentifierCreate(count, error);
    if (*error != ErrorNone) return NULL;
    for (Integer8 index = 0; index < count; index += 1) {
        Integer8 length = DecodeInteger8(bytes);
        Component *component = IdentifierComponentCreate(length, error);
        if (*error != ErrorNone) {
           IdentifierRemove(identifier, index);
           return NULL;
        }
        for (Integer8 index = 0; index < length; index += 1) component->codepoint[index] = DecodeInteger8(bytes);
        identifier->components[index] = component;
    }
    return identifier;
}

void IdentifierDealloc(VALUE *identifierValue) {
    Identifier *identifier = identifierValue;
    IdentifierRemove(identifier, identifier->count);
}
