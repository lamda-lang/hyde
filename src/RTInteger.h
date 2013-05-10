#ifndef RT_INTEGER
#define RT_INTEGER

#include "Runtime.h"

RTValue *RTIntegerValueBridge(RTInteger *integer);

/** -brief Deallocates the memory occupied by [integer].
    -arg integer The integer to deallocate. */
void RTIntegerDealloc(RTInteger *integer);

/** -brief Returns the size required by [integer] to encoding itself into a byte array.
    -arg integer The integer to examine.
    -return The encoding size of [integer], in bytes. */
RTSize RTIntegerEncodingSize(RTInteger *integer);

/** -brief Encodes [integer] into [buffer].
    -arg integer The integer to encode.
    -arg buffer The buffer into which to encode [integer].
    -effect [buffer] is overridden. */
void RTIntegerEncode(RTInteger *integer, RTByte *buffer);

/** -brief Creates an [RTInteger] by decoding [data].
    -arg data The data to decode.
    -return An [RTInteger] decoded from [data].
    -effect [*data] points one past the byte segment that contains the data. */
RTInteger *RTIntegerDecode(RTByte **data);

/** -brief Returns a boolean value that indicates whether [integer] and [other] are equal.
    -arg integer An integer.
    -arg other Another integer.
    -return [true] if [integer] and [other] are equal, otherwise [false]. */
bool RTIntegerEqual(RTInteger *integer, RTInteger *other);

/** -brief Returns a hash value based on the content of [integer].
    -important If two integers are equal, they have the same hash value.
    -arg integer The integer to examine.
    -return A hash value. */
RTInteger64Bit RTIntegerHash(RTInteger *integer);

/** -brief Returns the sum of [integer] and [other].
    -arg integer An integer.
    -arg other Another integer.
    -return An [RTInteger] representing the sum of [integer] and [other]. */
RTInteger *RTIntegerSum(RTInteger *integer, RTInteger *other);

#endif
