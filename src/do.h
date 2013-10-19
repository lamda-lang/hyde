#ifndef DO_H
#define DO_H

#include "runtime.h"

Bool DoDecode(Binary *binary, Integer32 *offset, Value **value);
Bool DoEval(Do *block, Context *context, Stack *stack);

#endif
