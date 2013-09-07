#include <builtin/identifier.h>

typedef struct Identifier Identifier;

struct Identifier {
    VALUE *type;
    Integer8 length;
    Integer8 codepoints[];
};

static Identifier *IdentifierCreate(Integer8 length, Error *error) {
    Identifier *identifier = MemoryAlloc(sizeof(Identifier) + sizeof(Integer8) * length, error);
    if (error != NULL) return NULL;
    identifier->type = RuntimeValueForConstant(ConstantIdentifierType);
    identifier->length = length;
    return identifier;
}

VALUE *IdentifierDecode(Byte **bytes, Error *error) {
    Integer8 length = DecodeInteger8(bytes);
    Identifier *identifier = IdentifierCreate(length, error);
    if (error != NULL) return NULL;
    for (Integer8 index = 0; index < length; index += 1) identifier->codepoints[index] = DecodeInteger8(bytes);
    return identifier;
}

void IdentifierDealloc(VALUE *identifierValue) {
    MemoryDealloc(identifierValue);
}
