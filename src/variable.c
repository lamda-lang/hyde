#include "variable.h"

typedef struct {
    VALUE *type;
    Integer8 length;
    Integer8 codepoints[];
} Variable;

static Variable *VariableCreate(Integer8 length, Error *error) {
    Variable *variable = MemoryAlloc(sizeof(Variable) + sizeof(Integer8) * length, error);
    if (error != NULL) {
        return NULL;
    }
    variable->type = RuntimeVariableType;
    variable->length = length;
    return variable;
}

VALUE *VariableDecode(Byte **bytes, Error *error) {
    Integer8 length = DecodeInteger8(bytes);
    Variable *variable = VariableCreate(length, error);
    if (error != NULL) {
        return NULL;
    }
    for (Integer8 index = 0; index < length; index += 1) {
        variable->codepoints[index] = DecodeInteger8(bytes);
    }
    return variable;
}

void VariableDealloc(VALUE *variableValue) {
    MemoryDealloc(variableValue);
}
