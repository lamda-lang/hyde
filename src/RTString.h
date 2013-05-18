#ifndef RT_STRING
#define RT_STRING

#include "Runtime.h"

RTValue *RTStringValueBridge(RTString *string);

/** -brief Deallocates the memory occupied by [string].
    -arg string The string to deallocate. */
void RTStringDealloc(RTString *string);

/** -brief Creates an [RTString] by decoding [data].
    -arg data The data to decode.
    -return An [RTString] decoded from [data].
    -effect [*data] points one past the byte segment that contains the data. */
RTString *RTStringDecode(RTByte **data);

/** -brief Returns a boolean value that indicates whether [string] and [other] are equal.
    -arg string A string.
    -arg other Another string.
    -return [true] if [string] and [other] are equal, otherwise [false]. */
bool RTStringEqual(RTString *string, RTString *other);

/** -brief Returns a hash value based on the content of [string].
    -important If two strings are equal, they have the same hash value.
    -arg string The string to examine.
    -return A hash value. */
RTInteger64Bit RTStringHash(RTString *string);

RTString *RTStringConcatenate(RTString *string, RTString *other);

RTError RTStringWriteToFile(RTString *string, RTFile file);

#endif
