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
void RTModuleDealloc(void *module_RModule);

/**  */
void RTModuleSetKeyValueIndexAtIndex(RTModule module, RTInteger32Bit keyIndex, RTInteger32Bit valueIndex, RTInteger32Bit index);

/** */
void RTModuleFetch(RTModule module, RTPrimitive *reg);

/**  */
RTPrimitive RTModuleGetValueForKey(RTModule module, RTPrimitive key);

RTInteger32Bit RTModuleHash(void *module_RTModule);

RTBool RTModuleEqual(void *module_RTModule, void *other_RTModule);

#endif
