#ifndef RT_INTEGER
#define RT_INTEGER

#include "runtime.h"

RTValue *RTIntegerValueBridge(RTInteger *integer);

/** -brief Deallocates the memory occupied by [integer].
    -arg integer The integer to deallocate. */
void RTIntegerDealloc(RTValue *integer_RTInteger);

/** -brief Creates an [RTInteger] by decoding [data].
    -arg data The data to decode.
    -return An [RTInteger] decoded from [data].
    -effect [*data] points one past the byte segment that contains the data. */
RTInteger *RTIntegerDecode(RTByte **data);

/** -brief Returns a hash value based on the content of [integer].
    -important If two integers are equal, they have the same hash value.
    -arg integer The integer to examine.
    -return A hash value. */
RTInteger64Bit RTIntegerHash(RTValue *integer_RTInteger);

/** -brief Returns the sum of [integer] and [other].
    -arg integer An integer.
    -arg other Another integer.
    -return An [RTInteger] representing the sum of [integer] and [other]. */
RTInteger *RTIntegerSum(RTInteger *integer, RTInteger *other);

#endif
