/** @module RTValue */

#ifndef RT_VALUE
#define RT_VALUE

#include "Runtime.h"

/**  */
RTValue RTValueCreateIdentifier(RTIdentifier id);

RTValue RTValueCreateList(RTList list);

RTValue RTValueCreateModule(RTModule module);

RTValue RTValueCreateString(RTString string);

void RTValueDealloc(RTValue value);

RTIdentifier RTValueGetIdentifier(RTValue value);

RTList RTValueGetList(RTValue value);

RTModule RTValueGetModule(RTValue value);

RTString RTValueGetString(RTValue value);

RTInteger32Bit RTValueHash(RTValue value, RTBool recursive);

RTBool RTValueEqual(RTValue value, RTValue other);

#endif
