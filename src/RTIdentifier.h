#ifndef RT_IDENTIFIER
#define RT_IDENTIFIER

#include "runtime.h"

RTValue *RTIdentifierValueBridge(RTIdentifier *id);

/** -brief Deallocates the memory occupied by [id].
    -arg id The identifier to deallocate. */
void RTIdentifierDealloc(RTValue *id_RTIdentifier);

/** -brief Creates an [RTIdentifier] by decoding [data].
    -arg data The data to decode.
    -return An [RTIdentifier] decoded from [data].
    -effect [*data] points one past the byte segment that contains the data. */
RTIdentifier *RTIdentifierDecode(RTByte **data);

/** -brief Returns a hash value based on the content of [id].
    -important If two identifiers are equal, they have the same hash value.
    -arg id The identifier to examine.
    -return A hash value. */
RTInteger64Bit RTIdentifierHash(RTValue *id_RTIdentifier);

#endif
