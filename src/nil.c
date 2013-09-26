#include "nil.h"

Size NilSize(Nil *nil) {
    return 0;
}

Size NilEncode(Nil *nil, Byte **bytes) {
    return 0;
}

Nil *NilDecode(Byte **bytes, Error *error) {
    return NULL;
}

Bool NilEqual(Nil *nil, Nil *other) {
    return TRUE;
}

Size NilRelease(Nil *nil) {
    return 0;
}
