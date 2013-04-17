#ifndef RT_VALUE
#define RT_VALUE

#include "Runtime.h"

/** -brief Creates an [RTValue].
    -return An [RTValue], or [NULL] if creation fails. */
RTValue RTValueCreate(void);

/** -brief Deallocates the memory occupied by [value].
    -arg value The value to deallocate. */
void RTValueDealloc(RTValue value);

/** -brief Sets [id] as the primitive of [value].
    -arg value The value in which the primitive is to be changed.
    -arg id The primitive of [value].
    -effect The primitive reference of [value] is set to [id]. */
void RTValueSetIdentifier(RTValue value, RTIdentifier id);

/** -brief Sets [id] as the primitive of [value].
    -arg value The value in which the primitive is to be changed.
    -arg id The primitive of [value].
    -effect The primitive reference of [value] is set to [id]. */
void RTValueSetInteger(RTValue value, RTInteger integer); 

/** -brief Sets [lambda] as the primitive of [value].
    -arg value The value in which the primitive is to be changed.
    -arg map The primitive of [value].
    -effect The primitive reference of [value] is set to [lambda]. */
void RTValueSetLambda(RTValue value, RTLambda lambda);

/** -brief Sets [list] as the primitive of [value].
    -arg value The value in which the primitive is to be changed.
    -arg map The primitive of [value].
    -effect The primitive reference of [value] is set to [list]. */
void RTValueSetList(RTValue value, RTList list);

/** -brief Sets [map] as the primitive of [value].
    -arg value The value in which the primitive is to be changed.
    -arg map The primitive of [value].
    -effect The primitive reference of [value] is set to [map]. */
void RTValueSetMap(RTValue value, RTMap map);

/** -brief Sets [string] as the primitive of [value].
    -arg value The value in which the primitive is to be changed.
    -arg string The primitive of [value].
    -effect The primitive reference of [value] is set to [string]. */
void RTValueSetString(RTValue value, RTString string);

/** -brief Returns the primitive of [value].
    -arg value The value to examine.
    -return The primitive of [value].
    -warning Access to a member of the return value is invalid if its type is not the same type of the primitive set. */
RTPrimitive RTValueGetPrimitive(RTValue value);

/** -brief Returns a hash value based on the content of [value].
    -important If two values are equal, they have the same hash value.
    -arg value The value to examine.
    -return A hash value. */
RTInteger64Bit RTValueHash(RTValue value);

/** -brief Returns a boolean value that indicates whether [value] and [other] are equal.
    -arg value A value.
    -arg other Another value.
    -return [TRUE] if [value] and [other] are equal, otherwise [FALSE]. */
RTBool RTValueEqual(RTValue value, RTValue other);

#endif
