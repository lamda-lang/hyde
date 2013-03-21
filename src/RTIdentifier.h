#ifndef RT_IDENTIFIER
#define RT_IDENTIFIER

#include "Runtime.h"

/** @brief Creates an @code{RTIdentifier}.
    @arg length The number of characters of the identifier.
    @return An code{RTIdentifier}, or @code{NULL} if creation fails. */
RTIdentifier RTIdentifierCreate(RTInteger8Bit length);

/** @brief Deallocates the memory occupied by @code{id}.
    @arg id The identifier to deallocate. */
void RTIdentifierDealloc(RTIdentifier id);

/** @brief Initializes @code{id} by decoding @code{data}.
    @arg id The identifier to initialize.
    @arg data The data to decode.
    @arg length The count of characters in @code{data}.
    @effect The content of @code{id} is overridden.
    @effect @code{*data} points one past the byte segment that contains the data. */
void RTIdentifierDecode(RTIdentifier id, RTByte **data, RTInteger8Bit length);

/** @brief Returns a boolean value that indicates whether @code{id} and @code{other} are equal.
    @arg id An identifier.
    @arg other Another identifier.
    @return @code{TRUE} if @code{id} and @code{other} are equal, otherwise @code{FALSE}. */
RTBool RTIdentifierEqual(RTIdentifier id, RTIdentifier other);

/** @brief Returns a hash value based on the content of @code{id}.
    @important If two identifiers are equal, they have the same hash value.
    @arg id The identifier.
    @return A hash value. */
RTInteger32Bit RTIdentifierHash(RTIdentifier id);

#endif
