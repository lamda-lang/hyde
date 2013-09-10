#include <builtin/float.h>

typedef struct Float Float;
typedef union Binary Binary;

struct Float {
    Float64 value;
};

static Value *FloatCreate(Float64 value) {
    Float *fpv = MemoryAlloc(sizeof(Float), error);
    if (fpv == NULL)
        return NULL;
    fpv->value = value;
    return ValueCreate(ModelFloat, fpv);
}

Value *FloatDecode(Byte **bytes) {
    Float64 value = DecodeFloat64(bytes);
    return FloatCreate(value);
}

Bool FloatEqual(void *floatData, void *otherData) {
    Float *fpv = floatData;
    Float *other = otherData;
    return fpv->value == other->value;
}

void FloatRelease(void *floatData) {
    MemoryDealloc(floatData);
}
