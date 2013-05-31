#ifndef STACK_H
#define STACK_H

#include "api.h"

Stack *StackCreate(Integer32 capacity, Error *error);

void StackDealloc(Stack *stack);

Status StackBuildNextFrame(Stack *stack, Integer32 count, Error *error);

void StackPushNextFrame(Stack *stack);

void StackPullTopFrame(Stack *stack);

Value **StackValuesFromTopFrame(Stack *stack);

Value **StackArgsFromTopFrame(Stack *stack);

Value **StackArgsFromNextFrame(Stack *stack);

Value **StackResultFromTopFrame(Stack *stack);

#endif
