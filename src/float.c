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
    return sizeof(Integer8) + sizeof(Float64);
}

void FLoatEncode(Float *fpn, Byte **bytes) {
    EncodeInteger8(OPCODE_FLOAT, bytes);
    EncodeFloat64(fpn->value, bytes);
}

Float *FloatDecode(Byte **bytes, Error *error) {
    Float64 value = DecodeFloat64(bytes);
    return FloatCreate(value, error);
}

Bool FloatEqual(Float *fpn, Float *other) {
    return fpn->value == other->value;
}

Size FloatRelease(Float *fpn) {
    MemoryDealloc(fpn);
    return sizeof(Float);
}
