#include "runtime.h"

#define MAJOR 0
#define MINOR 0

VALUE *RuntimeLoad(Byte *bytes, Error *error) {
    Integer8 major = DecodeInteger8(&bytes);
    Integer8 minor = DecodeInteger8(&bytes);
    if (major != MAJOR || minor < MINOR) {
        *error = ErrorInvalidBytecodeVersion;
        return NULL;
    }
    return DecodeValue(&bytes, error);
}

VALUE *RuntimeEval(VALUE *value, Error *error) {
    return NULL;
}
