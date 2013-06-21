#ifndef STACK_H
#define STACK_H

#include "api.h"

Stack *StackCreate(Integer32 length, Error *error);
void StackDealloc(Stack *stack);
Status StackPushFrame(Stack *stack, Integer32 count, Error *error);
void StackPullFrame(Stack *stack);
Value **StackFrameValues(Stack *stack);

#endif
