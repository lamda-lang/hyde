#include "nil.h"

Bool NilDecode(Binary *binary, Integer32 *offset, Value **value) {
    *value = ValueCreateNil(NULL);
    return TRUE;
}
