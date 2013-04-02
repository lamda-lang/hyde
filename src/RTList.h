#ifndef RT_LIST
#define RT_LIST

#include "Runtime.h"

/** -brief Creates an [RTList].
    -arg length The number of elements of the list.
    -return An [RTList], or [NULL] if creation fails. */
RTList RTListCreate(RTInteger32Bit length);

/** -brief Deallocates the memory occupied by [list].
    -arg list The list to deallocate. */
void RTListDealloc(RTList list);

/** -brief Sets [value] for [list] at [index].
    -arg list The listi into which the value is being changed. 
    -arg value The value to set at [index].
    -arg index The index at whoch to set [value]. 
    -effect The value of [list] at [index] is overridden. */
void RTListSetValueAtIndex(RTList list, RTValue value, RTInteger32Bit index);

/** -brief Returns the value at [index].
    -arg list The list.
    -arg index The index of the list.
    -return The value at [index]. */
RTValue RTListGetValueAtIndex(RTList list, RTInteger32Bit index);

/** -brief Returns a boolean value that indicates whether [list] and [other] are equal.
    -arg list A list.
    -arg other Another list.
    -return [TRUE] if [list] and [other] are equal, otherwise [FALSE]. */
RTBool RTListEqual(RTList list, RTList other);

/** -brief Returns a hash value based on the content of [list].
    -important If two lists are equal, they have the same hash value.
    -arg list The list.
    -arg recursive If [TRUE], the hash value is calculated recursively.
    -warning Recursively calculated hash values can result in infinite loops if an element cycle exists.
    -return A hash value. */
RTInteger32Bit RTListHash(RTList list, RTBool recursive);

#endif
