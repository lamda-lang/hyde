#ifndef RT_COLLECT
#define RT_COLLECT

#include "Runtime.h"

void RTCollectValue(RTValue *value);

void RTCollectRetainValue(RTValue *value);

void RTCollectReleaseValue(RTValue *value);

#endif
