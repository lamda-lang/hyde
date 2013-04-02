#ifndef RT_STRING
#define RT_STRING

#include "Runtime.h"

/** -brief Creates an @code{RTString}.
    -arg length The number of characters of the string.
    -return An code{RTString}, or [NULL] if creation fails. */
RTString RTStringCreate(RTInteger32Bit length);

/** -brief Deallocates the memory occupied by [string].
    -arg string The string to deallocate. */
void RTStringDealloc(RTString string);

/** */
RTSize RTStringEncodingSize(RTString);

/** missing */
void RTStringEncode(RTString string, RTByte *data);

/** -brief Initializes [string] by decoding [data].
    -arg string The string to initialize.
    -arg data The data to decode.
    -arg length The count of characters in [data].
    -effect The content of [string] is overridden.
    -effect [*data] points one past the byte segment that contains the data. */
void RTStringDecode(RTString string, RTByte **data, RTInteger32Bit length);

/** -brief Returns a boolean value that indicates whether [string] and [other] are equal.
    -arg string A string.
    -arg other Another string.
    -return [TRUE] if [string] and [other] are equal, otherwise [FALSE]. */
RTBool RTStringEqual(RTString string, RTString other);

/** -brief Returns a hash value based on the content of [string].
    -important If two strings are equal, they have the same hash value.
    -arg string The string.
    -return A hash value. */
RTInteger32Bit RTStringHash(RTString string);

#endif
