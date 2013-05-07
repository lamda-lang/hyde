#ifndef RT_MAP
#define RT_MAP

#include "Runtime.h"

RTValue RTMapValueBridge(RTMap map);

RTMap RTMapDecode(RTByte **data);

/** -brief Deallocates the memory occupied by [map].
    -arg map The map to deallocate. */
void RTMapDealloc(RTMap map);

/** -brief Sets a given key-value pair in [map].
    -warning Setting two keys that are equal is an error.
    -arg map The map into which the pair is being set. 
    -arg value The value for [key].
    -arg key The key for [value].
    -effect References to [key] and [value] are stored in [map]. */
void RTMapSetValueForKey(RTMap map, RTValue value, RTValue key);

/** -brief Returns the value associated with [key].
    -arg map The map to examine.
    -arg key The key for which to return the corresponding value.
    -return The value associated with [key], or NULL if no value is associated with [key]. */
RTValue RTMapGetValueForKey(RTMap map, RTValue key);

/** -brief Returns a hash value based on the content of [map].
    -important If two maps are equal, they have the same hash value.
    -arg map The map to examine.
    -return A hash value. */
RTInteger64Bit RTMapHash(RTMap map);

/** -brief Returns a boolean value that indicates whether [map] and [other] are equal.
    -arg map A map.
    -arg other Another map.
    -return [TRUE] if [map] and [other] are equal, otherwise [FALSE]. */
RTBool RTMapEqual(RTMap map, RTMap other);

void RTMapEnumerateKeys(RTMap map, RTBlock block);

void RTMapEnumerateValues(RTMap map, RTBlock block);

#endif
