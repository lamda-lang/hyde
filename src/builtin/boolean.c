#include <builtin/boolean.h>

typedef struct Boolean Boolean;

struct Boolean {
    Bool truth;
};

static Boolean *BooleanCreate(Bool truth, Error *error) {
    Boolean *boolean = MemoryAlloc(sizeof(Boolean), error);
    if (*error != ErrorNone) return NULL;
    boolean->truth = truth;
    return boolean;
}

static void BooleanDealloc(Boolean *boolean) {
    MemoryDealloc(boolean);
}

static Value *BooleanValue(Bool truth, Error *error) {
    Boolean *boolean = BooleanCreate(TRUE, error);
    if (*error != ErrorNone) return NULL;
    return ValueCreate(BuiltinBoolean, boolean, error);
}

Value *BooleanDecodeTrue(Byte **bytes, Error *error) {
    return BooleanValue(TRUE, error);
}

Value *BooleanDecodeFalse(Byte **bytes, Error *error) {
    return BooleanValue(FALSE, error);
}

void BooleanRelease(void *booleanModel) {
    BooleanDealloc(booleanModel);
}

Bool BooleanEqual(void *booleanModel, void *otherModel) {
    Boolean *boolean = booleanModel;
    Boolean *other = otherModel;
    return boolean->truth == other->truth;
}
