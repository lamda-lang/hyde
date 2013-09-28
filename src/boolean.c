#include "boolean.h"

struct Boolean {
    Bool truth;
};

static Boolean *BooleanCreate(Bool truth, Error *error) {
    Boolean *boolean = MemoryAlloc(sizeof(Boolean), error);
    if (ERROR(error))
        return NULL;
    boolean->truth = truth;
    return boolean;
}

Size BooleanSize(Boolean *boolean) {
    return BOOL_SIZE;
}

Size BooleanEncode(Boolean *boolean, Byte **bytes) {
    EncodeBool(boolean->truth, bytes);
    return BooleanSize(boolean);
}

Boolean *BooleanDecode(Byte **bytes, Error *error) {
    Bool truth = DecodeBool(bytes);
    return BooleanCreate(truth, error);
}

Value *BooleanEval(Value *value, Boolean *boolean, Value *context, Error *error) {
    return value;
}

Bool BooleanEqual(Boolean *boolean, Boolean *other) {
    return boolean->truth == other->truth;
}

Size BooleanRelease(Boolean *boolean) {
    MemoryDealloc(boolean);
    return sizeof(Boolean);
}
