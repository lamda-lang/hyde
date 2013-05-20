#ifndef RT_BUFFER
#define RT_BUFFER

#include "runtime.h"

RTBuffer *RTBufferCreate(void);

void RTBufferDealloc(RTBuffer *buffer);

RTStatus RTBufferAppend(RTBuffer *buffer, RTByte *source, RTSize size);

RTByte *RTBufferBytes(RTBuffer *buffer);

RTSize RTBufferSize(RTBuffer *buffer);

#endif
