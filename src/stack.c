#include "Stack.h"

typedef struct {
    Integer32 index;
    Integer32 count;
} Frame;

typedef struct {
    Integer32 capacity;
    Value **values;
    Frame top;
} Stack;

static Stack stackSingleton = {
    .capacity = 0,
    .values = NULL,
    .top.index = 0,
    .top.count = 0
};

Status StackPushFrame(Integer32 count, Error *error) {
}

void StackPullFrame(Integer32 count) {
}

Value **StackFrameValues(void) {
    return stackSingleton.values;
}
