#ifndef RT_VALUE
#define RT_VALUE

#include "Runtime.h"

RTValue RTValueCreate(void);

void RTValueDealloc(RTValue value, RTBool recursive);

void RTValueSetIdentifier(RTValue value, RTIdentifier id);

void RTValueSetList(RTValue value, RTList list);

void RTValueSetModule(RTValue value, RTModule module);

void RTValueSetString(RTValue value, RTString string);

RTPrimitive RTValueGetPrimitive(RTValue value);

RTInteger32Bit RTValueHash(RTValue value, RTBool recursive);

RTBool RTValueEqual(RTValue value, RTValue other);

#endif
