#ifndef RT_BASE
#define RT_BASE

#include "Runtime.h"

RTBase RTBaseInit(RTType type, RTFlag mask);

RTType RTBaseGetType(RTBase base);

RTBase RTBaseSetFlag(RTBase base, RTFlag flag, RTBool bool);

RTBool RTBaseGetFlag(RTBase base, RTFlag flag);

#endif
