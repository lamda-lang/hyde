#include <builtin/boolean.h>

struct Boolean {
    Bool truth;
};

static Value *BooleanCreate(Bool truth) {
    Boolean *boolean = MemoryAlloc(sizeof(Boolean));
    if (boolean == NULL)
        return NULL;
    boolean->truth = truth;
    return ValueCreate(MODEL_BOOLEAN, boolean);
}

Value *BooleanDecodeTrue(Byte **bytes) {
    return BooleanCreate(TRUE);
}

Value *BooleanDecodeFalse(Byte **bytes) {
    return BooleanCreate(FALSE);
}

Size BooleanRelease(Boolean *boolean) {
    MemoryDealloc(boolean);
    return sizeof(Boolean);
}

Bool BooleanEqual(Boolean *boolean, Boolean *other) {
    return boolean->truth == other->truth;
}
