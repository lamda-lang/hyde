#ifndef RT_VALUE
#define RT_VALUE

#include "Runtime.h"

RTValue RTValueCreateIdentifier(RTIdentifier id, RTPool);

RTValue RTValueCreateInteger(RTInteger integer);

RTValue RTValueCreateLambda(RTLambda lambda);

RTValue RTValueCreateList(RTList list);

RTValue RTValueCreateMap(RTMap map);

RTValue RTValueCreateString(RTString string);

RTValue RTValueCreateNil(void);

RTValue RTValueCreateBool(RTBool boolean);

/** -brief Deallocates the memory occupied by [value].
    -arg value The value to deallocate. */
void RTValueDealloc(RTValue value);

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

/** -brief Marks [value] recursively.
    -arg The value to mark.
    -effect [value] and all values reachable by [value] are marked. */
void RTValueMark(RTValue value);

/** -brief Unmarks [value].
    -value The value to unmark.
    -return [TRUE] if [value] is marked, otherwise [FALSE].
    -effect Unmarks [value]. */
RTBool RTValueResetMark(RTValue value);

#endif
