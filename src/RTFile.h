#ifndef RT_FILE
#define RT_FILE

#include "runtime.h"

RTError RTFileRead(RTFile file, RTBuffer *buffer);

RTError RTFileWrite(RTFile file, RTBuffer *buffer);

#endif
