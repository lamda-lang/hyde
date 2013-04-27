#ifndef RT_POOL
#define RT_POOL

#include "Runtime.h"

RTPool RTPoolBuild(void);

RTValue RTPoolNewValue(RTPool pool);

void RTPoolDrain(RTPool pool, RTValue root);

#endif
