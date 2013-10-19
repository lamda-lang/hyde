#ifndef WHEN_H
#define WHEN_H

#include "runtime.h"

Bool WhenDecode(Binary *binary, Integer32 *offset, Value **value);
Bool WhenEval(When *block, Context *context, Stack *stack);

#endif
