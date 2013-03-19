/** @module RTList */

#ifndef RT_LIST
#define RT_LIST

#include "Runtime.h"

/**  */
RTList RTListCreate(RTInteger32Bit length);

/**  */
void RTListDealloc(void *list_RTList);

/**  */
void RTListSetRegisterIndexAtIndex(RTList list, RTInteger32Bit regIndex, RTInteger32Bit index);

/**  */
RTPrimitive RTListGetPrimitiveAtIndex(RTList list, RTInteger32Bit index);

/**  */
void RTListFetch(RTList list, RTPrimitive *reg);

RTBool RTListEqual(void *list_RTList, void *other_RTList);

RTInteger32Bit RTListHash(void *list_RTList);

#endif
