#ifndef RT_IDENTIFIER
#define RT_IDENTIFIER

#include "Runtime.h"

/** -brief Deallocates the memory occupied by [id].
    -arg id The identifier to deallocate. */
void RTIdentifierDealloc(RTIdentifier id);

/** -brief Returns the size required by [id] to encoding itself into a byte array.
    -arg id The identifier to examine.
    -return The encoding size of [id], in bytes. */
RTSize RTIdentifierEncodingSize(RTIdentifier id);

/** -brief Encodes [id] into [buffer].
    -arg id The identifier to encode.
    -arg buffer The buffer into which to encode [id].
    -effect [buffer] is overridden. */
void RTIdentifierEncode(RTIdentifier id, RTByte *buffer);

/** -brief Creates an [RTIdentifier] by decoding [data].
    -arg data The data to decode.
    -return An [RTIdentifier] decoded from [data].
    -effect [*data] points one past the byte segment that contains the data. */
RTIdentifier RTIdentifierDecode(RTByte **data);

/** -brief Returns a boolean value that indicates whether [id] and [other] are equal.
    -arg id An identifier.
    -arg other Another identifier.
    -return [TRUE] if [id] and [other] are equal, otherwise [FALSE]. */
RTBool RTIdentifierEqual(RTIdentifier id, RTIdentifier other);

/** -brief Returns a hash value based on the content of [id].
    -important If two identifiers are equal, they have the same hash value.
    -arg id The identifier to examine.
    -return A hash value. */
RTInteger64Bit RTIdentifierHash(RTIdentifier id);

#endif
