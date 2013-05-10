#ifndef RT_BOOLEAN
#define RT_BOOLEAN

#include "Runtime.h"

RTValue *RTBooleanValueBridge(RTBoolean *boolean);

RTBoolean *RTBooleanCreate(bool truth);

void RTBooleanDealloc(RTBoolean *boolean);

#endif
