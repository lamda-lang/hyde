#ifbdef STACK_H
#define STACK_H

#include "runtime.h"

Stack *StackCreate(Integer32 count);
void StackPushValue(Stack *stack, Value *value);
Value *StackPopValue(Stack *stack);
void StackRaiseException(Stack *stack, Value *exception);

#endif
