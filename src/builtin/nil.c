#include <builtin/nil.h>

Value *NilDecode(Byte **bytes, Error *error) {
    return ValueCreate(ModelNil, NULL);
}

Bool NilEqual(void *nilData, void *otherData) {
    return TRUE;
}
