#include <builtin/boolean.h>

typedef struct Boolean Boolean;

struct Boolean {
    Bool truth;
};

static Value *BooleanCreate(Bool truth) {
    Boolean *boolean = MemoryAlloc(sizeof(Boolean), error);
    if (boolean == NULL)
        return NULL;
    boolean->truth = truth;
    return ValueCreate(ModelBoolean, boolean);
}

Value *BooleanDecodeTrue(Byte **bytes) {
    return BooleanCreate(TRUE);
}

Value *BooleanDecodeFalse(Byte **bytes) {
    return BooleanValue(FALSE);
}

void BooleanRelease(void *booleanData) {
    MemoryDealloc(booleanData);
}

Bool BooleanEqual(void *booleanData, void *otherData) {
    Boolean *boolean = booleanData;
    Boolean *other = otherData;
    return boolean->truth == other->truth;
}
