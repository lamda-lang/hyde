#include "constant.h"

static Value *Constants[] = {
    [CONSTANT_NIL] = NULL,
    [CONSTANT_BOOLEAN_TRUE] = NULL,
    [CONSTANT_BOOLEAN_FALSE] = NULL
};

void ConstantInit(Error *error) {
}

Value *ConstantValue(Constant constant) {
    return NULL;
}

void ConstantDealloc(void) {
}
