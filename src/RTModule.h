#ifndef RT_MODULE
#define RT_MODULE

#include "Runtime.h"

/** -brief Creates an [RTModule].
    -arg capacity The number of key-value pairs of the module.
    -return An [RTModule], or [NULL] if creation fails. */
RTModule RTModuleCreate(RTInteger32Bit capacity);

/** -brief Deallocates the memory occupied by [module].
    -arg module The module to deallocate. */
void RTModuleDealloc(RTModule module);

/** -brief Sets a given key-value pair in [module].
    -warning Setting two keys that are equal is an error.
    -arg module The module.
    -arg value The value for [key].
    -arg key The key for [value].
    -effect References to [key] and [value] are stored in [module].
    -effect The capacity of [module] is decreased by 1. */
void RTModuleSetValueForKey(RTModule module, RTValue value, RTValue key);

/** -brief Returns the value associated with [key].
    -arg module
    -arg key The key for which to return the corresponding value.
    -return The value associated with [key], or NULL if no value is associated with [key]. */
RTValue RTModuleGetValueForKey(RTModule module, RTValue key);

/** -brief Returns a hash value based on the content of [module].
    -important If two modules are equal, they have the same hash value.
    -arg module The module.
    -arg recursive If [TRUE], the hash value is calculated recursively.
    -warning Recursively calculated hash values can result in infinite loops if an element cycle exists.
    -return A hash value. */
RTInteger32Bit RTModuleHash(RTModule module, RTBool recursive);

/** -brief Returns a boolean value that indicates whether [module] and [other] are equal.
    -arg module A module.
    -arg other Another module.
    -return [TRUE] if [module] and [other] are equal, otherwise [FALSE]. */
RTBool RTModuleEqual(RTModule module, RTModule other);

#endif
