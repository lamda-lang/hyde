/** @module RTPrimitive */

#ifndef RT_PRIMITIVE
#define RT_PRIMITIVE

#include "Runtime.h"

/**  */
RTPrimitive RTPrimitiveCreate(void *object, RTType type);

/**  */
void RTPrimitiveDealloc(RTPrimitive primitive);

/** */
void *RTPrimitiveGetObject(RTPrimitive primitive);

/** */
RTInteger32Bit RTPrimitiveHash(RTPrimitive primitive);

/** */
RTBool RTPrimitiveEqual(RTPrimitive object, RTPrimitive other);

#endif
