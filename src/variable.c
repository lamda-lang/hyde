#include "variable.h"

typedef struct {
    VALUE *type;
    Integer8 length;
    Integer8 codepoints[];
} Variable;

static Variable *VariableCreate(Integer8 length, VALUE **error) {
    Variable *variable = MemoryAlloc(sizeof(Variable) + sizeof(Integer8) * length, error);
    if (error != NULL) {
        return NULL;
    }
    variable->type = RuntimeVariableType;
    variable->length = length;
    return variable;
}

VALUE *VariableDecode(Byte **bytes, VALUE **error) {
    Integer8 length = DecodeInteger8FLE(bytes);
    Variable *variable = VariableCreate(length, error);
    if (error != NULL) {
        return NULL;
    }
    for (Integer8 index = 0; index < length; index += 1) {
        variable->codepoints[index] = DecodeInteger8FLE(bytes);
    }
    return variable;
}

void VariableDealloc(VALUE *variableValue) {
    MemoryDealloc(variableValue);
}

Integer64 VariableHash(VALUE *variableValue) {
    Variable *variable = variableValue;
    return variable->length;
}

Bool VariableEqual(VALUE *variableValue, VALUE *otherValue) {
    Variable *variable = variableValue;
    Variable *other = otherValue;
    return variable->length == other->length
        && MemoryEqual(variable->codepoints, other->codepoints, sizeof(Integer8) * variable->length);
}
