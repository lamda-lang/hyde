#include "kernel.h"

Value *KernelDecode(Value **args) {
    Binary *binary = ValueBinaryPrimitive(args[0]);
    Integer32 offset = 0;
    Value *value = BinaryDecodeValue(binary, &offset);
    if (value == NULL)
        /* missing */
        return NULL;
    return value;
}
