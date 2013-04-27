#include "RTMap.h"

struct RTElement {
  RTValue key;
  RTValue value;
};

struct RTMap {
  RTInteger32Bit length;
  struct RTElement element[];
};

static inline RTInteger32Bit RTMapIndex(RTMap map, RTValue value, RTInteger32Bit offset) {
  return (RTValueHash(value) + offset) % map->length;
}

RTMap RTMapCreate(RTInteger32Bit capacity) {
  RTInteger32Bit length = capacity * 2;
  RTSize size = sizeof(struct RTMap) + sizeof(struct RTElement) * length;
  RTMap map = RTMemoryAlloc(size);
  if (map == NULL) {
    return NULL;
  }
  map->length = length;
  for (RTInteger32Bit index = 0; index < length; index += 1) {
    map->element[index].key = NULL;
    map->element[index].value = NULL;
  }
  return map;
}

void RTMapDealloc(RTMap map) {
  RTMemoryDealloc(map);
}

void RTMapSetValueForKey(RTMap map, RTValue value, RTValue key) {
  RTInteger32Bit index = RTMapIndex(map, key, 0);
  while (map->element[index].key != NULL) {
    index = RTMapIndex(map, key, index);
  }
  map->element[index].key = key;
  map->element[index].value = value;
}

RTValue RTMapGetValueForKey(RTMap map, RTValue key) {
  RTInteger32Bit index = RTMapIndex(map, key, 0);
  while (map->element[index].key != NULL && RTValueEqual(key, map->element[index].key) == FALSE) {
    index = RTMapIndex(map, key, index);
  }
  return map->element[index].value;
}

RTInteger64Bit RTMapHash(RTMap map) {
  return map->length;
}

RTBool RTMapEqual(RTMap map, RTMap other) {
  if (map->length != other->length) {
    return FALSE;
  }
  for (RTInteger32Bit index = 0; index < map->length; index += 1) {
    RTValue mapKey = map->element[index].key;
    if (mapKey != NULL) {
      RTValue mapValue = RTMapGetValueForKey(map, mapKey);
      RTValue otherValue = RTMapGetValueForKey(other, mapKey);
      if (otherValue == NULL || RTValueEqual(mapValue, otherValue) == FALSE) {
	return  FALSE;
      }
    }
  }
  return TRUE;
}

void RTMapEnumerateKeys(RTMap map, RTBlock block) {
  for (RTInteger32Bit index = 0; index < map->length; index += 1) {
    block(map->element[index].key);
  }
}

void RTMapEnumerateValues(RTMap map, RTBlock block) {
  for (RTInteger32Bit index = 0; index < map->length; index += 1) {
    block(map->element[index].value);
  }
}
