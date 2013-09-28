#include "float.h"

struct Float {
    Float64 value;
};

static Float *FloatCreate(Float64 value, Error *error) {
    Float *fpn = MemoryAlloc(sizeof(Float), error);
    if (ERROR(error))
        return NULL;
    fpn->value = value;
    return fpn;
}

Size FloatSize(Float *fpn) {
    return FLOAT_64_SIZE;
}

Size FloatEncode(Float *fpn, Byte **bytes) {
    EncodeFloat64(fpn->value, bytes);
    return FloatSize(fpn);
}

Float *FloatDecode(Byte **bytes, Error *error) {
    Float64 value = DecodeFloat64(bytes);
    return FloatCreate(value, error);
}

Value *FloatEval(Value *value, Float *fpn, Value *context, Error *error) {
    return value;
}

Bool FloatEqual(Float *fpn, Float *other) {
    return fpn->value == other->value;
}

Size FloatRelease(Float *fpn) {
    MemoryDealloc(fpn);
    return sizeof(Float);
}
