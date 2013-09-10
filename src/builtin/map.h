#ifndef BUILTIN_MAP_H
#define BUILTIN_MAP_H

#include <runtime.h>

Value *MapDecode(Byte **bytes);
void MapRelease(void *mapData);
Bool MapEqual(void *mapData, void *otherData); 

#endif
