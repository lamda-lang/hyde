#ifndef LIST_H
#define LIST_H

#include "runtime.h"

Value *ListDecode(Binary *binary, Integer32 *offset);
Bool ListEval(List *list, Stack *stack);

#endif
