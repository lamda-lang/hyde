#include "boolean.h"

struct Boolean {
    Bool truth;
};

Value *BooleanCreate(Bool truth) {
    Boolean *boolean = MemoryAllocUnit(sizeof(Boolean));
    boolean->truth = truth;
    return ValueCreateBoolean(boolean);
}

Bool BooleanTruth(Boolean *boolean) {
    return boolean->truth;
}

Bool BooleanDecode(Binary *binary, Integer32 *offset, Value **value) {
    Bool truth;
    if (!BinaryDecodeBool(binary, offset, &truth))
        return FALSE;
    *value = BooleanCreate(truth);
    return TRUE;
}

Bool BooleanEqual(Boolean *boolean, Boolean *other) {
    return boolean->truth == other->truth;
}
