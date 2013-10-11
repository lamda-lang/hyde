#include "float.h"

struct Float {
    Float64 value;
};

static Value *FloatCreate(Float64 value) {
    Float *fpn = MemoryAllocUnit(sizeof(Float));
    fpn->value = value;
    return ValueCreateFloat(fpn);

Value *FloatDecodePrimitive(Binary *binary, Integer32 *offset) {
    Float64 value;
    if (!BinaryDecodeFloat64(binary, offset, &value))
        return NULL;
    return FloatCreate(value);
}
