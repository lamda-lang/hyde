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

typedef struct{
    Register *root;
    Frame top;
    Integer32 capacity;
} Stack;

static Stack stack = {
    .capacity = 0,
    .root = NULL,
    .top.index = 0,
    .top.length = 0
};

Status StackPushFrame(Integer32 count, Error *error) {
    Frame top = {
        .index = stack.top.index + stack.top.length,
	.length = HEADER_LENGTH + count
    };
    if (top.index + top.length > stack.capacity) { 
        Integer32 capacity = (stack.capacity + count) * 2;
        Register *root = MemoryRealloc(stack.root, capacity, error);
        if (root == NULL) {
            goto returnError;
        }
        stack.capacity = capacity;
        stack.root = root;
    }
    stack.top = top;
    return StatusSuccess;

returnError:
    return StatusFailure;
}

void StackPullFrame(void) {
    stack.top = stack.root[stack.top.index].frame;
}

Value **StackFrameValues(void) {
    return &stack.root[stack.top.index + HEADER_LENGTH].value;
}
