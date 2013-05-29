#ifndef KERNEL_H
#define KERNEL_H

#include "api.h"

Status KernelIntegerSum(Stack *stack, Exception *exception);

Status KernelStringConcatenate(Stack *stack, Exception *exception);

#endif
