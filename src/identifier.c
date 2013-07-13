#include <string.h>
#include "identifier.h"

struct Identifier {
    Value base;
    Integer8 length;
    Integer8 codepoint[];
};

typedef struct {
    Integer8 length;
    Integer8 codepoint[];
} Model;

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

void *IdentifierDecode(Byte **bytes, Error *error) {
    Integer8 length = DecodeInteger8FLE(bytes);
    Model *model = MemoryAlloc(sizeof(Model) + sizeof(Integer8) * length, error);
    if (model == NULL) {
        goto returnError;
    }
    for (Integer8 index = 0; index < length; index += 1) {
        model->codepoint[index] = DecodeInteger8FLE(bytes);
    }
    return model;

returnError:
    return NULL;
}

Value *IdentifierEval(void *data, Code *code, Value **context, Bool pure, Error *error) {
    Model *model = data;
    Identifier *id = Create(model->length, error);
    if (id == NULL) {
        goto returnError;
    }
    MemoryCopy(model->codepoint, id->codepoint, sizeof(Integer8) * model->length);
    return BridgeFromIdentifier(id);

returnError:
    return NULL;
}

Value *IdentifierCreateWithCharacters(Char *chars, Error *error) {
    Integer8 length = strnlen(chars, 0XF) & 0XF;
    Identifier *id = Create(length, error);
    if (id == NULL) {
        goto returnError;
    }
    MemoryCopy(chars, id->codepoint, length);
    return BridgeFromIdentifier(id);

returnError:
    return NULL;
}

void IdentifierDealloc(Value *idValue) {
    MemoryDealloc(idValue);
}

Integer64 IdentifierHash(Value *idValue) {
    return BridgeToIdentifier(idValue)->length;
}

Bool IdentifierEqual(Value *idValue, Value *otherValue) {
    Identifier *id = BridgeToIdentifier(idValue);
    Identifier *other = BridgeToIdentifier(otherValue);
    return id->length == other->length &&
           MemoryEqual(id->codepoint, other->codepoint, sizeof(Integer8) * id->length);
}
