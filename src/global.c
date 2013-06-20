#include "global.h"

Value *GlobalNil = NULL;
Value *GlobalBooleanTrue = NULL;
Value *GlobalBooleanFalse = NULL;
Stack *GlobalStack = NULL;

Status GlobalInit(Error *error) {
    return StatusSuccess;
}
