#include "nil.h"

Value *NilDecodePrimitive(Binary *binary, Integer32 *offset) {
    return ValueCreateNil(NULL);
}
