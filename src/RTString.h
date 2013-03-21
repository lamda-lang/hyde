#ifndef RT_STRING
#define RT_STRING

#include "Runtime.h"

/** @brief Creates an @code{RTString}.
    @arg length The number of characters of the string.
    @return An code{RTString}, or @code{NULL} if creation fails. */
RTString RTStringCreate(RTInteger32Bit length);

/** @brief Deallocates the memory occupied by @code{string}.
    @arg string The string to deallocate. */
void RTStringDealloc(RTString string);

/** @brief Initializes @code{string} by decoding @code{data}.
    @arg string The string to initialize.
    @arg data The data to decode.
    @arg length The count of characters in @code{data}.
    @effect The content of @code{string} is overridden.
    @effect @code{*data} points one past the byte segment that contains the data. */
void RTStringDecode(RTString string, RTByte **data, RTInteger32Bit length);

/** @brief Returns a boolean value that indicates whether @code{string} and @code{other} are equal.
    @arg string A string.
    @arg other Another string.
    @return @code{TRUE} if @code{string} and @code{other} are equal, otherwise @code{FALSE}. */
RTBool RTStringEqual(RTString string, RTString other);

/** @brief Returns a hash value based on the content of @code{string}.
    @important If two strings are equal, they have the same hash value.
    @arg string The string.
    @return A hash value. */
RTInteger32Bit RTStringHash(RTString string);

#endif
