/** @module RTModule */

#ifndef RT_MODULE
#define RT_MODULE

#include "Runtime.h"

/** @brief
    @arg capacity
    @return */
RTModule RTModuleCreate(RTInteger32Bit capacity);

/** @brief
    @arg module
    @effect */
void RTModuleDealloc(RTModule module);

/**  */
void RTModuleSetKeyValueIndexAtIndex(RTModule module, RTInteger32Bit keyIndex, RTInteger32Bit valueIndex, RTInteger32Bit index);

/** */
void RTModuleFetch(RTModule module, RTValue *reg);

/**  */
RTValue RTModuleGetValueForKey(RTModule module, RTValue key);

RTInteger32Bit RTModuleHash(RTModule module);

RTBool RTModuleEqual(RTModule module, RTModule other);

#endif
