#include "stack.h"

#define MIN_SIZE 32

struct Stack {
    Integer32 size;
    Integer32 count;
    Value *exception;
    Value **values;
}

static void StackIncrease(Stack *stack) {
    Value **values = MemoryAllocArray(sizeof(Value *), stack->size * 2);
    for (Integer32 index = 0; index < stack->count)
        values[index] = stack->values[index];
    MemoryDealloc(stack->values);
    stack->size *= 2;
    stack->values = values;
}

Stack *StackCreate(Integer32 size) {
    if (size < MIN_SIZE)
        size = MIN_SIZE;
    Stack *stack = MemoryAllocUnit(sizeof(Stack));
    stack->size = size;
    stack->count = 0;
    stack->exception = NULL;
    return stack;
}

void StackPushValue(Stack *stack, Value *value) {
    if (stack->count == stack->size)
        StackIncrease(stack);
    stack->values[stack->count] = value;
    stack->count += 1;
}

Value *StackPopValue(Stack *stack) {
    stack->count -= 1;
    return stack->values[stack->count];
}

void StackRaiseException(Stack *stack, Value *exception) {
    stack->exception = exception;
}
