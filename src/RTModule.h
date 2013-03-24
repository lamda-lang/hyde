#ifndef RT_MODULE
#define RT_MODULE

#include "Runtime.h"

/** @brief Creates an @code{RTModule}.
    @arg capacity The number of key-value pairs of the module.
    @return An code{RTModule}, or @code{NULL} if creation fails. */
RTModule RTModuleCreate(RTInteger32Bit capacity);

/** @brief Deallocates the memory occupied by @code{module}.
    @arg module The module to deallocate. */
void RTModuleDealloc(RTModule module);

/** @brief Sets a given key-value pair in @code{module}.
    @warning Setting two keys that are equal is an error.
    @arg module The module.
    @arg value The value for @code{key}.
    @arg key The key for @code{value}.
    @effect References to @code{key} and @code{value} are stored in @code{module}.
    @effect The capacity of @code{module} is decreased by 1. */
void RTModuleSetValueForKey(RTModule module, RTValue value, RTValue key);

/** @brief Returns the value associated with @coe{key}.
    @arg module
    @arg key The key for which to return the corresponding value.
    @return The value associated with @code{key}, or NULL if no value is associated with @code{key}. */
RTValue RTModuleGetValueForKey(RTModule module, RTValue key);

/** @brief Returns a hash value based on the content of @code{module}.
    @important If two modules are equal, they have the same hash value.
    @arg module The module.
    @arg recursive If @code{TRUE}, the hash value is calculated recursively.
    @warning Recursively calculated hash values can result in infinite loops if an element cycle exists.
    @return A hash value. */
RTInteger32Bit RTModuleHash(RTModule module, RTBool recursive);

/** @brief Returns a boolean value that indicates whether @code{module} and @code{other} are equal.
    @arg module A module.
    @arg other Another module.
    @return @code{TRUE} if @code{module} and @code{other} are equal, otherwise @code{FALSE}. */
RTBool RTModuleEqual(RTModule module, RTModule other);

#endif
