#ifndef STACK_H
#define STACK_H

#include "api.h"

Stack *StackCreate(Integer32Bit capacity);

void StackDealloc(Stack *stack);

bool StackBuildNextFrame(Stack *stack, Integer32Bit count);

void StackPushNextFrame(Stack *stack);

Value *StackReturnFromTopFrame(Stack *stack);

void StackCleanTopFrame(Stack *stack);

void StackSetResultInTopFrame(Stack *stack, Value *result);

Value *StackGetValueFromTopFrame(Stack *stack, Integer32Bit index);

void StackSetValueInTopFrame(Stack *stack, Value *value, Integer32Bit index);

Value *StackGetArgFromTopFrame(Stack *stack, Integer8Bit index);

void StackSetArgInNextFrame(Stack *stack, Value *value, Integer8Bit index);

#endif
