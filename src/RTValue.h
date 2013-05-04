#ifndef RT_VALUE
#define RT_VALUE

#include "Runtime.h"

#define VALUE(primitive) ((RTValue)primitive)
#define BASE(type) 0

RTBool RTValueEqual();

RTInteger64Bit RTValueHash();

/** -brief Deallocates the memory occupied by [value].
    -arg value The value to deallocate. */
void RTValueDealloc(RTValue value);

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
