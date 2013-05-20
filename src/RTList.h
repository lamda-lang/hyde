#ifndef RT_LIST
#define RT_LIST

#include "runtime.h"

RTValue *RTListValueBridge(RTList *list);

RTList *RTListDecode(RTByte **data);

/** -brief Deallocates the memory occupied by [list].
    -arg list The list to deallocate. */
void RTListDealloc(RTValue *list_RTList);

/** -brief Sets [value] for [list] at [index].
    -arg list The list into which the value is being set. 
    -arg value The value to set at [index].
    -arg index The index at which to set [value]. 
    -effect The value of [list] at [index] is overridden. */
void RTListSetValueAtIndex(RTList *list, RTValue *value, RTInteger32Bit index);

/** -brief Returns the value at [index].
    -arg list The list to examine.
    -arg index The index of the value.
    -return The value at [index]. */
RTValue *RTListGetValueAtIndex(RTList *list, RTInteger32Bit index);

/** -brief Returns a hash value based on the content of [list].
    -important If two lists are equal, they have the same hash value.
    -arg list The list to examine.
    -return A hash value. */
RTInteger64Bit RTListHash(RTValue *list_RTValue);

void RTListEnumerate(RTValue *list_RTList, RTBlock *block);

#endif
