#ifndef RT_BOOLEAN
#define RT_BOOLEAN

#include "runtime.h"

RTValue *RTBooleanValueBridge(RTBoolean *boolean);

RTBoolean *RTBooleanCreate(bool truth);

void RTBooleanDealloc(RTBoolean *boolean);

bool RTBooleanEqual(RTBoolean *boolean, RTBoolean *other);

RTInteger64Bit RTBooleanHash(RTBoolean *boolean);

#endif
