#ifndef RT_MAP
#define RT_MAP

#include "Runtime.h"

RTValue *RTMapValueBridge(RTMap *map);

RTMap *RTMapDecode(RTByte **data);

/** -brief Deallocates the memory occupied by [map].
    -arg map The map to deallocate. */
void RTMapDealloc(RTValue *map_RTMap);

/** -brief Sets a given key-value pair in [map].
    -warning Setting two keys that are equal is an error.
    -arg map The map into which the pair is being set. 
    -arg value The value for [key].
    -arg key The key for [value].
    -effect References to [key] and [value] are stored in [map]. */
void RTMapSetValueForKey(RTMap *map, RTValue *value, RTValue *key);

/** -brief Returns a hash value based on the content of [map].
    -important If two maps are equal, they have the same hash value.
    -arg map The map to examine.
    -return A hash value. */
RTInteger64Bit RTMapHash(RTValue *map_RTMap);

void RTMapEnumerate(RTValue *map_RTValue, RTBlock *block);

#endif
