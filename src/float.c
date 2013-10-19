#include "float.h"

struct Float {
    Float64 value;
};

static Value *FloatCreate(Float64 value) {
    Float *fpn = MemoryAllocUnit(sizeof(Float));
    fpn->value = value;
    return ValueCreateFloat(fpn);
}

Bool FloatDecode(Binary *binary, Integer32 *offset, Value **value) {
    Float64 data;
    if (!BinaryDecodeFloat64(binary, offset, &data))
        return FALSE;
    *value = FloatCreate(data);
    return TRUE;
}

Value *FloatEqual(Float *fpn, Float *other) {
    Bool equal = fpn->value == other->value;
    return BooleanCreate(equal);
}
