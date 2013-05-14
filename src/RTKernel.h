#ifndef RT_KERNEL
#define RT_KERNEL

#include "Runtime.h"

RTError RTKernelEqual(RTInteger8Bit arity, RTStack *stack);

RTError RTKernelStringConcatenate(RTInteger8Bit arity, RTStack *stack);

#endif
