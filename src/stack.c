#include "Stack.h"

#define HEADER_LENGTH 1
#define RESULT_OFFSET 1
#define ARG_OFFSET 2
#define VALUE_OFFSET 1

typedef struct {
    Integer32 index;
    Integer32 length;
} Frame;

typedef union {
    Value *value;
    Frame frame;
} Element;

struct Stack {
    Element *root;
    Frame top;
    Frame next;
    Integer32 capacity;
};

static inline void RemoveGarbageFlagWithRoot(Value *root) {
    if (!ValueFlagSet(root, FlagMark)) {
        ValueSetFlag(root, FlagMark, true);
        ValueSetFlag(root, FlagGarbage, false);
        ValueEnumerate(root, RemoveGarbageFlagWithRoot);
    }
}

static inline void RemoveMarkFlagWithRoot(Value *root) {
    if (ValueFlagSet(root, FlagMark)) {
        ValueSetFlag(root, FlagMark, false);
        ValueEnumerate(root, RemoveMarkFlagWithRoot);
    }
}

Stack *StackCreate(Integer32 capacity, Error *error) {
    Stack *stack = MemoryAlloc(sizeof(Stack), error);
    if (stack == NULL) {
        goto returnError;
    }
    Element *root = MemoryAlloc(sizeof(Element) * capacity, error);
    if (root == NULL) {
        goto deallocStack;
    }
    stack->capacity = capacity;
    stack->root = root;
    stack->top.index = 0;
    stack->top.length = 0;
    stack->next.index = 0;
    stack->next.length = 0;
    return stack;

deallocStack:
    MemoryDealloc(stack);
returnError:
    return NULL;
}

void StackDealloc(Stack *stack) {
    MemoryDealloc(stack->root);
    MemoryDealloc(stack);
}

Status StackBuildNextFrame(Stack *stack, Integer32 count, Error *error) {
    Frame top = stack->top;
    Integer32 length = HEADER_LENGTH + count;
    if (top.index + top.length + length > stack->capacity) { 
        Integer32 capacity = stack->capacity * 2;
        Element *root = MemoryRealloc(stack->root, capacity, error);
        if (root == NULL) {
            goto returnError;
        }
        stack->capacity = capacity;
        stack->root = root;
    }
    stack->next.index = top.index + top.length;
    stack->next.length = length;
    return StatusSuccess;

returnError:
    return StatusFailure;
}

void StackPushNextFrame(Stack *stack) {
    stack->root[stack->next.index].frame = stack->top;
    stack->top = stack->next;
}

void StackPullTopFrame(Stack *stack) {
    Frame top = stack->top;
    Value *root = stack->root[top.index + VALUE_OFFSET].value;
    RemoveGarbageFlagWithRoot(root);
    RemoveMarkFlagWithRoot(root);
    for (Integer32 index = VALUE_OFFSET; index < top.length; index += 1) {
        Value *value = stack->root[top.index + index].value;
        if (ValueFlagSet(value, FlagGarbage)) {
            ValueDealloc(value);
        }
    }
    stack->top = stack->root[top.index].frame;
}

Value **StackValuesFromTopFrame(Stack *stack) {
    return &stack->root[stack->top.index + VALUE_OFFSET].value;
}

Value **StackArgsFromTopFrame(Stack *stack) {
    return &stack->root[stack->top.index + ARG_OFFSET].value;
}

Value **StackArgsFromNextFrame(Stack *stack) {
    return &stack->root[stack->next.index + ARG_OFFSET].value;
}

Value **StackResultFromTopFrame(Stack *stack) {
    return &stack->root[stack->top.index + RESULT_OFFSET].value;
}
