#include <builtin/float.h>

struct Float {
    Float64 value;
};

static Float *FloatCreate(Float64 value) {
    Float *fpn = MemoryAlloc(sizeof(Float));
    if (fpn == NULL)
        return NULL;
    fpn->value = value;
    return fpn;
}

Float *FloatDecode(Byte **bytes) {
    Float64 value = DecodeFloat64(bytes);
    return FloatCreate(value);
}

Bool FloatEqual(Float *fpn, Float *other) {
    return fpn->value == other->value;
}

Size FloatRelease(Float *fpn) {
    MemoryDealloc(fpn);
    return sizeof(Float);
}
