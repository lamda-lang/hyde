#ifndef STACK_H
#define STACK_H

#include "runtime.h"

Stack *StackCreate(Integer32 count);
void StackDealloc(Stack *stack);
void StackPushValue(Stack *stack, Value *value);
Value *StackPopValue(Stack *stack);
void StackReplaceTop(Stack *stack, Value *value);

#endif
