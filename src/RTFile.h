#ifndef RT_FILE
#define RT_FILE

#include "runtime.h"

RTError RTFileRead(RTFile file, RTData *data);

RTError RTFileWrite(RTFile file, void *buffer, RTSize size);

#endif
