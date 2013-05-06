#ifndef RT_NIL
#define RT_NIL

#include "Runtime.h"

RTValue RTNilValueBridge(RTNil nil);

RTNil RTNilCreate(void);

void RTNilDealloc(RTNil nil);

#endif
