#include "boolean.h"

struct Boolean {
    Bool truth;
};

Value *BooleanCreate(Bool truth) {
    Boolean *boolean = MemoryAllocUnit(sizeof(Boolean));
    boolean->truth = truth;
    return ValueCreateBoolean(boolean);
}

Bool BooleanDecode(Binary *binary, Integer32 *offset, Value **value) {
    Bool truth;
    if (!BinaryDecodeBool(binary, offset, &truth))
        return FALSE;
    *value = BooleanCreate(truth);
    return TRUE;
}

Value *BooleanEqual(Boolean *boolean, Boolean *other) {
    Bool equal = boolean->truth == other->truth;
    return BooleanCreate(equal);
}
