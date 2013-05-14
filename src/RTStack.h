#ifndef RT_STACK
#define RT_STACK

#include "Runtime.h"

RTStack *RTStackCreate(RTInteger32Bit capacity);

void RTStackDealloc(RTStack *stack);

RTError RTStackBuildNextFrame(RTStack *stack, RTInteger32Bit count);

void RTStackPushNextFrame(RTStack *stack);

RTValue *RTStackReturnFromTopFrame(RTStack *stack);

void RTStackSetResultInTopFrame(RTStack *stack, RTValue *result);

RTValue *RTStackGetValueFromTopFrame(RTStack *stack, RTInteger32Bit index);

void RTStackSetValueInTopFrame(RTStack *stack, RTValue *value, RTInteger32Bit index);

RTValue *RTStackGetArgFromTopFrame(RTStack *stack, RTInteger8Bit index);

void RTStackSetArgInNextFrame(RTStack *stack, RTValue *value, RTInteger8Bit index);

#endif
