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
} Register;

struct Stack {
    Register *root;
    Frame top;
    Integer32 capacity;
};

static void RemoveGarbageFlagWithRoot(Value *root) {
    if (!ValueFlagSet(root, FlagMark)) {
        ValueSetFlag(root, FlagMark, true);
        ValueSetFlag(root, FlagGarbage, false);
        ValueEnumerate(root, RemoveGarbageFlagWithRoot);
    }
}

static void RemoveMarkFlagWithRoot(Value *root) {
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
    Register *root = MemoryAlloc(sizeof(Register) * capacity, error);
    if (root == NULL) {
        goto deallocStack;
    }
    stack->capacity = capacity;
    stack->root = root;
    stack->top.index = 0;
    stack->top.length = 0;
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

Status StackPushFrame(Stack *stack, Integer32 count, Error *error) {
    Frame next = {
        .index = stack->top.index + stack->top.length,
	.length = HEADER_LENGTH + count
    };
    if (next.index + next.length > stack->capacity) { 
        Integer32 capacity = stack->capacity * 2;
        Register *root = MemoryRealloc(stack->root, capacity, error);
        if (root == NULL) {
            goto returnError;
        }
        stack->capacity = capacity;
        stack->root = root;
    }
    stack->top = next;
    return StatusSuccess;

returnError:
    return StatusFailure;
}

void StackPullFrame(Stack *stack) {
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

Value **StackFrameValues(Stack *stack) {
    return &stack->root[stack->top.index + VALUE_OFFSET].value;
}

Value **StackFrameArgs(Stack *stack) {
    return &stack->root[stack->top.index + ARG_OFFSET].value;
}

Value **StackFrameResult(Stack *stack) {
    return &stack->root[stack->top.index + RESULT_OFFSET].value;
}
