#include <builtin/nil.h>

Value *NilDecode(Byte **bytes, Error *error) {
    return ValueCreate(BuiltinNil, NULL, error);
}

Bool NilEqual(void *nilModel, void *otherModel) {
    return TRUE;
}
