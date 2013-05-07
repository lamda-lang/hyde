#ifndef RT_BASE
#define RT_BASE

#include "Runtime.h"

RTBase RTBaseInit(RTType type, RTFlag mask);

RTType RTBaseGetType(RTBase base);

RTBase RTBaseSetFlag(RTBase base, RTFlag flag, RTBool value);

RTBool RTBaseGetFlag(RTBase base, RTFlag flag);

RTBool RTBaseEqualFlag(RTBase base, RTBase other, RTFlag flag);

#endif
