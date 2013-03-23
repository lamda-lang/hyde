#ifndef RT_MODULE
#define RT_MODULE

#include "Runtime.h"

RTModule RTModuleCreate(RTInteger32Bit capacity);

void RTModuleDealloc(RTModule module);

RTValue RTModuleGetValueForKey(RTModule module, RTValue key);

RTInteger32Bit RTModuleHash(RTModule module, RTBool recursive);

RTBool RTModuleEqual(RTModule module, RTModule other);

#endif
