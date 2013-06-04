#ifndef STACK_H
#define STACK_H

#include "api.h"

Stack *StackCreate(Integer32 capacity, Error *error);

void StackDealloc(Stack *stack);

Status StackPushFrame(Stack *stack, Integer32 count, Error *error);

void StackPullFrame(Stack *stack);

Value **StackFrameValues(Stack *stack);

Value **StackFrameArgs(Stack *stack);

Value **StackFrameResult(Stack *stack);

#endif
