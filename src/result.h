#ifndef RESULT_H
#define RESULT_H

#include "runtime.h"

Bool ResultDecode(Binary *binary, Integer32 *offset, Value **value);
Bool ResultEval(Result *result, Context *context, Stack *stack);
Bool ResultEqual(Result *result, Result *other);

#endif
