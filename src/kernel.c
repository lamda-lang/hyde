#include "kernel.h"

void *KernelDecode(Stack *stack);
    Value *binaryValue = StackPopValue(stack);
    Binary *binary = ValueBinaryPrimitive(binaryValue);
    Integer32 offset = 0;
    Value *value = BinaryDecodeValue(binary, &offset);
    if (value == NULL)
        goto out;
    return;

out:
    Exception *exception = ExceptionInvalidBinary(binaryValue);
    StackRaiseException(exception);
}
