#ifndef RT_LIST
#define RT_LIST

#include "Runtime.h"

/** @brief Creates an @code{RTList}.
    @arg length The number of elements of the list.
    @return An code{RTList}, or @code{NULL} if creation fails. */
RTList RTListCreate(RTInteger32Bit length);

/** @brief Deallocates the memory occupied by @code{list}.
    @arg list The list to deallocate. */
void RTListDealloc(RTList list);

/** @brief Returns the value at @code{index}.
    @arg list The list.
    @arg index The index of the list.
    @return The value at @code{index}. */
RTValue RTListGetValueAtIndex(RTList list, RTInteger32Bit index);

/** @brief Returns a boolean value that indicates whether @code{list} and @code{other} are equal.
    @arg list A list.
    @arg other Another list.
    @return @code{TRUE} if @code{list} and @code{other} are equal, otherwise @code{FALSE}. */
RTBool RTListEqual(RTList list, RTList other);

/** @brief Returns a hash value based on the content of @code{list}.
    @important If two lists are equal, they have the same hash value.
    @arg list The list.
    @arg recursive If @code{TRUE}, the hash value is calculated recursively.
    @warning Recursively calculated hash values can result in infinite loops if an element cycle exists.
    @return A hash value. */
RTInteger32Bit RTListHash(RTList list, RTBool recursive);

#endif
