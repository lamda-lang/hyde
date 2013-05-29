#include "identifier.h"

struct Identifier {
    Value base;
    Integer8 length;
    Integer8 codepoint[];
};

static inline Identifier *Create(Integer8 length, Error *error) {
    Size size = sizeof(Identifier) + sizeof(Integer8) * length;
    Identifier *id = MemoryAlloc(size, error);
    if (id == NULL) {
        goto returnError;
    }
    id->base = TypeIdentifier;
    id->length = length;
    return id;

returnError:
    return NULL;
}

Value *IdentifierValueBridge(Identifier *id) {
    return (Value *)id;
}

void IdentifierDealloc(Value *idValue) {
    MemoryDealloc(idValue);
}

Identifier *IdentifierDecode(Byte **bytes, Error *error) {
    Integer8 length = DecodeInteger8FLE(bytes);
    Identifier *id = Create(length, error);
    if (id == NULL) {
        goto returnError;
    }
    for (Integer8 index = 0; index < length; index += 1) {
        id->codepoint[index] = DecodeInteger8FLE(bytes);
    }
    return id;

returnError:
    return NULL;
}

Integer64 IdentifierHash(Value *idValue) {
    Identifier *id = ValueIdentifierBridge(idValue);
    return id->length;
}
