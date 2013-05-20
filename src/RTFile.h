#ifndef RT_FILE
#define RT_FILE

#include "runtime.h"

RTStatus RTFileRead(RTFile file, RTBuffer *buffer);

RTStatus RTFileWrite(RTFile file, RTBuffer *buffer);

#endif
