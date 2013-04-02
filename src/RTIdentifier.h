#ifndef RT_IDENTIFIER
#define RT_IDENTIFIER

#include "Runtime.h"

/** -brief Deallocates the memory occupied by [id].
    -arg id The identifier to deallocate. */
void RTIdentifierDealloc(RTIdentifier id);

/** missing */
RTSize RTIdentifierEncodingSize(RTIdentifier id);

/** missing */
void RTIdentifierEncode(RTIdentifier id, RTByte *data);

/** -brief Creates an [id] by decoding [data].
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
    -arg id The identifier.
    -return A hash value. */
RTInteger32Bit RTIdentifierHash(RTIdentifier id);

#endif
