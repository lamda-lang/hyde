#ifndef RT_NIL
#define RT_NIL

#include "Runtime.h"

RTValue *RTNilValueBridge(RTNil *nil);

RTNil *RTNilCreate(void);

void RTNilDealloc(RTValue *nil_RTNil);

RTInteger64Bit RTNilHash(RTValue *nil_RTNil);

#endif
