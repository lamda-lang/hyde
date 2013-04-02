#ifndef RT_VALUE
#define RT_VALUE

#include "Runtime.h"

/** -brief Creates an [RTValue].
    -return An [RTValue], or [NULL] if creation fails. */
RTValue RTValueCreate(void);

/** -brief Deallocates the memory occupied by [value].
    -arg value The value to deallocate.
    -recursive If [TRUE], the primitive referenced by [value] is also deallocated.
    -warning [recursive] must be [FALSE] if no primitive is set. */
void RTValueDealloc(RTValue value, RTBool recursive);

/**  -brief Sets [id] as the primitive of [value].
     -arg value The value.
     -arg id The primitive of [value].
     -effect The primitive reference of [value] is set to [id]. */
void RTValueSetIdentifier(RTValue value, RTIdentifier id);

/**  -brief Sets [list] as the primitive of [value].
     -arg value The value.
     -arg module The primitive of [value].
     -effect The primitive reference of [value] is set to [list]. */
void RTValueSetList(RTValue value, RTList list);

/**  -brief Sets [module] as the primitive of [value].
     -arg value The value.
     -arg module The primitive of [value].
     -effect The primitive reference of [value] is set to [module]. */
void RTValueSetModule(RTValue value, RTModule module);

/**  -brief Sets [string] as the primitive of [value].
     -arg value The value.
     -arg string The primitive of [value].
     -effect The primitive reference of [value] is set to [string]. */
void RTValueSetString(RTValue value, RTString string);

/** -brief Returns the primitive of [value].
    -arg value The value.
    -return The primitive of [value].
    -warning Access to a member of the return value is invalid if its type is the same type of the primitive set. */
RTPrimitive RTValueGetPrimitive(RTValue value);

/** -brief Returns a hash value based on the content of [value].
    -important If two values are equal, they have the same hash value.
    -arg value The value.
    -arg recursive If [TRUE], the hash value is calculated recursively.
    -warning Recursively calculated hash values can result in infinite loops if an element cycle exists.
    -return A hash value. */
RTInteger32Bit RTValueHash(RTValue value, RTBool recursive);

/** -brief Returns a boolean value that indicates whether [value] and [other] are equal.
    -arg value A value.
    -arg other Another value.
    -return [TRUE] if [value] and [other] are equal, otherwise [FALSE]. */
RTBool RTValueEqual(RTValue value, RTValue other);

#endif
