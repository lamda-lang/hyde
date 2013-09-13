#include <builtin/float.h>

struct Float {
    Float64 value;
};

static Value *FloatCreate(Float64 value) {
    Float *fpv = MemoryAlloc(sizeof(Float));
    if (fpv == NULL)
        return NULL;
    fpv->value = value;
    return ValueCreate(MODEL_FLOAT, fpv);
}

Value *FloatDecode(Byte **bytes) {
    Float64 value = DecodeFloat64(bytes);
    return FloatCreate(value);
}

Bool FloatEqual(Float *fpv, Float *other) {
    return fpv->value == other->value;
}

Size FloatRelease(Float *fpv) {
    MemoryDealloc(fpv);
    return sizeof(Float);
}
