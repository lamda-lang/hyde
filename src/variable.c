#include "variable.h"

struct Variable {
    Type *type;
    Integer8 length;
    Integer8 codepoints[];
};

static Variable *VariableCreate(Integer8 length, VALUE **error) {
    Variable *token = MemoryAlloc(sizeof(Variable) + sizeof(Integer8) * length, error);
    if (error != NULL) {
        return NULL;
    }
    token->type = RuntimeVariableType;
    token->length = length;
    return token;
}

VALUE *VariableDecode(Byte **bytes, VALUE **error) {
    Integer8 length = DecodeInteger8FLE(bytes);
    Variable *token = VariableCreate(length, error);
    if (error != NULL) {
        return NULL;
    }
    for (Integer8 index = 0; index < length; index += 1) {
        token->codepoints[index] = DecodeInteger8FLE(bytes);
    }
    return BridgeFromVariable(token);
}

void VariableDealloc(VALUE *tokenValue) {
    MemoryDealloc(tokenValue);
}

Integer64 VariableHash(VALUE *tokenValue) {
    return BridgeToVariable(tokenValue)->length;
}

Bool VariableEqual(VALUE *tokenValue, VALUE *otherValue) {
    Variable *token = BridgeToVariable(tokenValue);
    Variable *other = BridgeToVariable(otherValue);
    return token->length == other->length
        && MemoryEqual(token->codepoints, other->codepoints, sizeof(Integer8) * token->length);
}
