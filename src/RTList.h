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

/** @brief Sets a register index of an element.
    @arg list The list.
    @arg regIndex The register index of an element.
    @arg index The index of the list.
    @effect The content of @code{list} ist overridden at @code{index}. */
void RTListSetRegisterIndexAtIndex(RTList list, RTInteger32Bit regIndex, RTInteger32Bit index);

/** @brief Returns the element at @code{index}.
    @arg list The list.
    @arg The index.
    @return The element at @code{index}. */
RTValue RTListGetValueAtIndex(RTList list, RTInteger32Bit index);

/** @brief Fetches the elements from @code{reg}.
    @arg list The list.
    @arg reg The register set.
    @effect The content of @code{list} is overridden. */
void RTListFetch(RTList list, RTValue *reg);

/** @brief Returns a boolean value that indicates whether @code{list} and @code{other} are equal.
    @arg list A list.
    @arg other Another list.
    @return @code{TRUE} if @code{list} and @code{other} are equal, otherwise @code{FALSE}. */
RTBool RTListEqual(RTList list, RTList other);

/** @brief Returns a hash value based on the content of @code{list}.
    @important If two lists are equal, they have the same hash value.
    @arg list The list.
    @return A hash value. */
RTInteger32Bit RTListHash(RTList list);

#endif
