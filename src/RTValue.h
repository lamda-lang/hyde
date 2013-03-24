#ifndef RT_VALUE
#define RT_VALUE

#include "Runtime.h"

/** @brief Creates an @code{RTValue}.
    @return An code{RTValue}, or @code{NULL} if creation fails. */
RTValue RTValueCreate(void);

/** @brief Deallocates the memory occupied by @code{value}.
    @arg value The value to deallocate.
    @recursive If @code{TRUE}, the primitive referenced by @code{value} is also deallocated.
    @warning @code{recursive} must be @code{FALSE} if no primitive is set. */
void RTValueDealloc(RTValue value, RTBool recursive);

/**  @brief Sets @code{id} as the primitive of @code{value}.
     @arg value The value.
     @arg id The primitive of @code{value}.
     @effect The primitive reference of @code{value} is set to @code{id}. */
void RTValueSetIdentifier(RTValue value, RTIdentifier id);

/**  @brief Sets @code{list} as the primitive of @code{value}.
     @arg value The value.
     @arg module The primitive of @code{value}.
     @effect The primitive reference of @code{value} is set to @code{list}. */
void RTValueSetList(RTValue value, RTList list);

/**  @brief Sets @code{module} as the primitive of @code{value}.
     @arg value The value.
     @arg module The primitive of @code{value}.
     @effect The primitive reference of @code{value} is set to @code{module}. */
void RTValueSetModule(RTValue value, RTModule module);

/**  @brief Sets @code{string} as the primitive of @code{value}.
     @arg value The value.
     @arg string The primitive of @code{value}.
     @effect The primitive reference of @code{value} is set to @code{string}. */
void RTValueSetString(RTValue value, RTString string);

/** @brief Returns the primitive of @code{value}.
    @arg value The value.
    @return The primitive of @code{value}.
    @warning Access to a member of the return value is invalid if its type is the same type of the primitive set. */
RTPrimitive RTValueGetPrimitive(RTValue value);

/** @brief Returns a hash value based on the content of @code{value}.
    @important If two values are equal, they have the same hash value.
    @arg value The value.
    @arg recursive If @code{TRUE}, the hash value is calculated recursively.
    @warning Recursively calculated hash values can result in infinite loops if an element cycle exists.
    @return A hash value. */
RTInteger32Bit RTValueHash(RTValue value, RTBool recursive);

/** @brief Returns a boolean value that indicates whether @code{value} and @code{other} are equal.
    @arg value A value.
    @arg other Another value.
    @return @code{TRUE} if @code{value} and @code{other} are equal, otherwise @code{FALSE}. */
RTBool RTValueEqual(RTValue value, RTValue other);

#endif
