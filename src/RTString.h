#ifndef RT_STRING
#define RT_STRING

#include "Runtime.h"

#define STRING(value) ((RTString)value)

/** -brief Deallocates the memory occupied by [string].
    -arg string The string to deallocate. */
void RTStringDealloc(RTString string);

/** -brief Returns the size required by [string] to encoding itself into a byte array.
    -arg string The string to examine.
    -return The encoding size of [string], in bytes. */
RTSize RTStringEncodingSize(RTString);

/** -brief Encodes [string] into [buffer].
    -arg string The string to encode.
    -arg buffer The buffer into which to encode [string].
    -effect [buffer] is overridden. */
void RTStringEncode(RTString string, RTByte *buffer);

/** -brief Creates an [RTString] by decoding [data].
    -arg data The data to decode.
    -return An [RTString] decoded from [data].
    -effect [*data] points one past the byte segment that contains the data. */
RTString RTStringDecode(RTByte **data);

/** -brief Returns a boolean value that indicates whether [string] and [other] are equal.
    -arg string A string.
    -arg other Another string.
    -return [TRUE] if [string] and [other] are equal, otherwise [FALSE]. */
RTBool RTStringEqual(RTString string, RTString other);

/** -brief Returns a hash value based on the content of [string].
    -important If two strings are equal, they have the same hash value.
    -arg string The string to examine.
    -return A hash value. */
RTInteger64Bit RTStringHash(RTString string);

#endif
