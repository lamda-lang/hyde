#ifndef RT_STACK
#define RT_STACK

#include "Runtime.h"

RTStack *RTStackCreate(RTInteger32Bit capacity);

void RTStackDealloc(RTStack *stack);

void RTStackClear(RTStack *stack);

RTInteger32Bit RTStackTopFrame(RTStack *stack);

RTError RTStackBuildFrame(RTStack *stack, RTInteger32Bit lenght);

void RTStackSetValueInFrame(RTStack *stack, RTValue *value, RTInteger32Bit index, RTInteger32Bit frame);

void RTStackSetValueInTopFrame(RTStack *stack, RTValue *value, RTInteger32Bit index);

RTValue *RTStackGetValueFromFrame(RTStack *stack, RTInteger32Bit index, RTInteger32Bit frame);

RTValue *RTStackGetValueFromTopFrame(RTStack *stack, RTInteger32Bit index);

void RTStackSetArgInFrame(RTStack *stack, RTValue *value, RTInteger8Bit index, RTInteger32Bit frame);

void RTStackSetArgInTopFrame(RTStack *stack, RTValue *value, RTInteger8Bit index);

RTValue *RTStackResultFromFrame(RTStack *stack, RTInteger32Bit frame);

RTValue *RTStackResultFromTopFrame(RTStack *stack);

void RTStackEnumerateValues(RTStack *stack, RTBlock *block);

#endif
