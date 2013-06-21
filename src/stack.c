#include "Stack.h"

#define HEADER_LENGTH 1

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
    Integer32 length;
};

Stack *StackCreate(Integer32 length, Error *error) {
    Stack *stack = MemoryAlloc(sizeof(Stack), error);
    if (stack == NULL) {
	goto returnError;
    }
    Register *root = MemoryAlloc(sizeof(Register) * length, error);
    if (root == NULL) {
	goto deallocStack;
    }
    stack->root = root;
    stack->length = length;
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
    Frame top = {
        .index = stack->top.index + stack->top.length,
	.length = HEADER_LENGTH + count
    };
    if (top.index + top.length > stack->length) { 
        Integer32 length = (stack->length + count) * 2;
        Register *root = MemoryRealloc(stack->root, length, error);
        if (root == NULL) {
            goto returnError;
        }
        stack->length = length;
        stack->root = root;
    }
    stack->top = top;
    return StatusSuccess;

returnError:
    return StatusFailure;
}

void StackPullFrame(Stack *stack) {
    stack->top = stack->root[stack->top.index].frame;
}

Value **StackFrameValues(Stack *stack) {
    return &stack->root[stack->top.index + HEADER_LENGTH].value;
}
