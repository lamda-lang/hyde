#include <builtin/float.h>

struct Float {
    Float64 value;
};

static Value *FloatCreate(Float64 value) {
    Float *fpn = MemoryAlloc(sizeof(Float));
    if (fpn == NULL)
        return NULL;
    fpn->value = value;
    return ValueCreate(MODEL_FLOAT, fpn);
}

Value *FloatDecode(Byte **bytes) {
    Float64 value = DecodeFloat64(bytes);
    return FloatCreate(value);
}

Value *FloatEqual(Float *fpn, Float *other) {
    return fpn->value == other->value ? VALUE_TRUE : VALUE_FALSE;
}

Size FloatRelease(Float *fpn) {
    MemoryDealloc(fpn);
    return sizeof(Float);
}
