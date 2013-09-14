#include <builtin/boolean.h>

struct Boolean {
    Bool truth;
};

Value *BooleanCreate(Bool truth) {
    Boolean *boolean = MemoryAlloc(sizeof(Boolean));
    if (boolean == NULL)
        return NULL;
    boolean->truth = truth;
    return ValueCreate(MODEL_BOOLEAN, boolean);
}

Size BooleanRelease(Boolean *boolean) {
    MemoryDealloc(boolean);
    return sizeof(Boolean);
}

Bool BooleanEqual(Boolean *boolean, Boolean *other) {
    return boolean->truth == other->truth;
}
