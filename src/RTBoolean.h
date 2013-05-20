#ifndef RT_BOOLEAN
#define RT_BOOLEAN

#include "runtime.h"

RTValue *RTBooleanValueBridge(RTBoolean *boolean);

RTBoolean *RTBooleanCreate(bool truth);

void RTBooleanDealloc(RTValue *boolean_RTBoolean);

RTInteger64Bit RTBooleanHash(RTValue *boolean_RTBoolean);

#endif
