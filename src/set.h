#ifndef SET_H
#define SET_H

#include "runtime.h"

Bool SetDecode(Binary *binary, Integer32 *offset, Value **value);
Bool SetEval(Set *set, Context *context, Stack *stack);

#endif
