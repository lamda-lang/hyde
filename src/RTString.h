/** @module RTString */

#ifndef RT_STRING
#define RT_STRING

#include "Runtime.h"

/**  */
RTString RTStringCreate(RTInteger32Bit length);

/**  */
void RTStringDealloc(void *string);

/**  */
void RTStringDecode(RTString string, RTByte **data, RTInteger32Bit length);

RTInteger32Bit RTStringHash(void *string_RTString);

RTBool RTStringEqual(void *string_RTString, void *other_RTString);

#endif
