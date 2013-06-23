#ifndef KERNEL_H
#define KERNEL_H

#include "api.h"

Value *KernelIntegerSum(Value **args, Integer8 count, Error *error);
Value *KernelStringConcatenate(Value **args, Integer8 count, Error *error);
Value *KernelIOPrint(Value **args, Integer8 count, Error *error);

#endif
