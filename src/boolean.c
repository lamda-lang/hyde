#include "boolean.h"

struct Boolean {
    Bool truth;
};

Value *BooleanCreate(Bool truth) {
    Boolean *boolean = MemoryAllocUnit(sizeof(Boolean));
    boolean->truth = truth;
    return ValueCreateBoolean(boolean);
}

Value *BooleanDecode(Binary *binary, Integer32 *offset) {
    Bool truth;
    if (!BinaryDecodeBool(binary, offset, &truth))
        return NULL;
    return BooleanCreate(truth);
}

Value *BooleanEqual(Boolean *boolean, Boolean *other) {
    Bool equal = boolean->truth == other->truth;
    return BooleanCreate(equal);
}
