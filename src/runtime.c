#include "runtime.h"

#define STACK_SIZE 256

int main(int argc, char **argv) {
    Stack *stack = StackCreate(STACK_SIZE);
    Byte *bytes = NULL;
    Integer32 count = 0;
    Value *binary = BinaryCreateValue(bytes, count);
    StackDealloc(stack);
}
