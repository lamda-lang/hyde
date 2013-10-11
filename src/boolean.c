#include "boolean.h"

struct Boolean {
    Bool truth;
};

static Value *BooleanCreate(Bool truth) {
    Boolean *boolean = MemoryAllocUnit(sizeof(Boolean));
    boolean->truth = truth;
    return ValueCreateBoolean(boolean);
}

Value *BooleanDecodePrimitive(Binary *binary, Integer32 *offset) {
    Bool truth;
    if (!BinaryDecodeBool(binary, offset, &truth))
        return NULL;
    return BooleanCreate(truth);
}
