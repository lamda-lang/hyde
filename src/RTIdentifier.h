#ifndef RT_IDENTIFIER
#define RT_IDENTIFIER

#include "Runtime.h"

/** -brief Creates an [RTIdentifier].
    -arg length The number of characters of the identifier.
    -return An [RTIdentifier], or [NULL] if creation fails. */
RTIdentifier RTIdentifierCreate(RTInteger8Bit length);

/** -brief Deallocates the memory occupied by [id].
    -arg id The identifier to deallocate. */
void RTIdentifierDealloc(RTIdentifier id);

/** missing */
RTSize RTIdentifierEncodingSize(RTIdentifier id);

/** missing */
void RTIdentifierEncode(RTIdentifier id, RTByte *data);

/** -brief Initializes [id] by decoding [data].
    -arg id The identifier to initialize.
    -arg data The data to decode.
    -arg length The count of characters in [data].
    -effect The content of [id] is overridden.
    -effect [*data] points one past the byte segment that contains the data. */
void RTIdentifierDecode(RTIdentifier id, RTByte **data, RTInteger8Bit length);

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
