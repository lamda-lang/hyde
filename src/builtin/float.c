#include <builtin/float.h>

typedef struct Float Float;
typedef union Binary Binary;

struct Float {
    Float64 value;
};

union Binary {
    Integer64 integer;
    Float64 IEEE754;
};

static Float *FloatCreate(Float64 value, Error *error) {
    Float *fpv = MemoryAlloc(sizeof(Float), error);
    if (*error != ErrorNone) return NULL;
    fpv->value = value;
    return fpv;
}

static void FloatDealloc(Float *fpv) {
    MemoryDealloc(fpv);
}

Value *FloatDecode(Byte **bytes, Error *error) {
    Binary binary = {
        .integer = DecodeInteger64(bytes)
    };
    Float *fpv = FloatCreate(binary.IEEE754, error);
    if (*error != ErrorNone) return NULL;
    return ValueCreate(BuiltinFloat, fpv, error);
}

Bool FloatEqual(void *floatModel, void *otherModel) {
    Float *fpv = floatModel;
    Float *other = otherModel;
    return fpv->value == other->value;
}

void FloatRelease(void *floatModel) {
    FloatDealloc(floatModel);
}
