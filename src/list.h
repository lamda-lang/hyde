#ifndef LIST_H
#define LIST_H

#include "runtime.h"

Bool ListDecode(Binary *binary, Integer32 *offset, Value **value);
Bool ListEval(List *list, Context *context, Stack *stack);

#endif
