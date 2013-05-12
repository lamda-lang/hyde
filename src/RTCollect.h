#ifndef RT_COLLECT
#define RT_COLLECT

#include "Runtime.h"

void RTCollectValue(RTValue *value);

void RTCollectMarkValue(RTValue *value);

void RTCollectUnmarkValue(RTValue *value);

#endif
