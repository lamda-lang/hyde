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

Stack *StackCreate(Integer32 capacity, Exception *exception) {
    Stack *stack = MemoryAlloc(sizeof(Stack), exception);
    if (stack == NULL) {
        goto returnError;
    }
    Element *root = MemoryAlloc(sizeof(Element) * capacity, exception);
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

Status StackBuildNextFrame(Stack *stack, Integer32 count, Exception *exception) {
    Frame top = stack->top;
    Integer32 length = HEADER_LENGTH + count;
    if (top.index + top.length + length > stack->capacity) { 
        Integer32 capacity = stack->capacity * 2;
        Element *root = MemoryRealloc(stack->root, capacity, exception);
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

Value *StackReturnFromTopFrame(Stack *stack) {
    Frame top = stack->top;
    Value *result = stack->root[top.index + VALUE_OFFSET].value;
    RemoveGarbageFlagWithRoot(result);
    RemoveMarkFlagWithRoot(result);
    for (Integer32 index = VALUE_OFFSET; index < top.length; index += 1) {
        Value *value = stack->root[top.index + index].value;
        if (ValueFlagSet(value, FlagGarbage)) {
            ValueDealloc(value);
        }
    }
    stack->top = stack->root[top.index].frame;
    return result;
}

void StackSetResultInTopFrame(Stack *stack, Value *result) {
    stack->root[stack->top.index + RESULT_OFFSET].value = result;
}

void StackRemoveTopFrame(Stack *stack) {

}

Value *StackGetValueFromTopFrame(Stack *stack, Integer32 index) {
    return stack->root[stack->top.index + VALUE_OFFSET + index].value;
}

void StackSetValueInTopFrame(Stack *stack, Value *value, Integer32 index, bool transient) {
    ValueSetFlag(value, FlagGarbage, true);
    stack->root[stack->top.index + VALUE_OFFSET + index].value = value;
}

Value **StackGetArgsFromTopFrame(Stack *stack) {
    return &stack->root[stack->top.index + ARG_OFFSET].value;
}

void StackSetArgInNextFrame(Stack *stack, Value *value, Integer8 index) {
    stack->root[stack->next.index + ARG_OFFSET + index].value = value;
}
