#include <string.h>
#include "identifier.h"

struct Identifier {
    Value base;
    Integer8 length;
    Integer8 codepoint[];
};

static Identifier *Create(Integer8 length, Error *error) {
    Identifier *id = MemoryAlloc(sizeof(Identifier) + sizeof(Integer8) * length, error);
    if (id == NULL) {
        goto returnError;
    }
    id->base = TypeIdentifier;
    id->length = length;
    return id;

returnError:
    return NULL;
}

Identifier *IdentifierCreateWithCharacters(Char *chars, Error *error) {
    Integer8 length = strnlen(chars, 0XF) & 0XF;
    Identifier *id = Create(length, error);
    if (id == NULL) {
	goto returnError;
    }
    MemoryCopy(chars, id->codepoint, length);
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

Value *IdentifierDecode(Byte **bytes, Error *error) {
    Integer8 length = DecodeInteger8FLE(bytes);
    Identifier *id = Create(length, error);
    if (id == NULL) {
        goto returnError;
    }
    for (Integer8 index = 0; index < length; index += 1) {
        id->codepoint[index] = DecodeInteger8FLE(bytes);
    }
    return IdentifierValueBridge(id);

returnError:
    return NULL;
}

Integer64 IdentifierHash(Value *idValue) {
    return ValueIdentifierBridge(idValue)->length;
}

Value *IdentifierEval(Value *idValue, bool pure, Error *error) {
    return idValue;
}
