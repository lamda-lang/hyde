#ifndef KERNEL_H
#define KERNEL_H

#include "api.h"

Value *KernelIntegerSum(Args *args, Error *error);

Value *KernelStringConcatenate(Args *args, Error *error);

#endif
