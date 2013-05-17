#ifndef RT_DATA
#define RT_DATA

#include "runtime.h"

RTData *RTDataCreate(void);

void RTDataDealloc(RTData *data);

RTError RTDataAppend(RTData *data, RTByte *source, RTSize size);

const RTByte *RTDataBytes(RTData *data);

RTSize RTDataSize(RTData *data);

#endif
