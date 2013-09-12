#include <builtin/nil.h>

Value *NilDecode(Byte **bytes) {
    return ValueCreate(ModelNil, NULL);
}

Bool NilEqual(void *nilData, void *otherData) {
    return TRUE;
}
