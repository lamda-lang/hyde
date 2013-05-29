#ifndef STACK_H
#define STACK_H

#include "api.h"

Stack *StackCreate(Integer32 capacity, Exception *exception);

void StackDealloc(Stack *stack);

Status StackBuildNextFrame(Stack *stack, Integer32 count, Exception *exception);

void StackPushNextFrame(Stack *stack);

Value *StackReturnFromTopFrame(Stack *stack);

void StackRemoveTopFrame(Stack *stack);

void StackSetResultInTopFrame(Stack *stack, Value *result);

Value *StackGetValueFromTopFrame(Stack *stack, Integer32 index);

void StackSetValueInTopFrame(Stack *stack, Value *value, Integer32 index, bool transient);

Value **StackGetArgsFromTopFrame(Stack *stack);

void StackSetArgInNextFrame(Stack *stack, Value *value, Integer8 index);

#endif
