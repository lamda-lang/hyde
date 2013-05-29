#ifndef KERNEL_H
#define KERNEL_H

#include "api.h"

Status KernelIntegerSum(Stack *stack, Error *error);

Status KernelStringConcatenate(Stack *stack, Error *error);

#endif
