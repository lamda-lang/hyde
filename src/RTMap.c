#include "RTMap.h"

struct RTElement {
  RTValue *key;
  RTValue *value;
};

struct RTMap {
  RTValue base;
  RTInteger32Bit length;
  struct RTElement element[];
};

static inline RTInteger32Bit Index(RTMap *map, RTValue *value, RTInteger32Bit offset) {
  return (RTValueHash(value) + offset) % map->length;
}

RTValue *RTMapValueBridge(RTMap *map) {
  return (RTValue *)map;
}

RTMap *RTMapDecode(RTByte **data) {
  RTInteger32Bit length = RTDecodeVBRInteger32Bit(data) * 2;
  RTSize size = sizeof(struct RTMap) + sizeof(struct RTElement) * length;
  RTMap *map = RTMemoryAlloc(size);
  if (map == NULL) {
    return NULL;
  }
  map->base = RTValueInit(RTTypeMap, RTFlagNone);
  map->length = length;
  for (RTInteger32Bit index = 0; index < length; index += 1) {
    map->element[index].key = NULL;
    map->element[index].value = NULL;
  }
  return map;
}

void RTMapDealloc(RTMap *map) {
  RTMemoryDealloc(map);
}

void RTMapSetValueForKey(RTMap *map, RTValue *value, RTValue *key) {
  RTInteger32Bit index = Index(map, key, 0);
  while (map->element[index].key != NULL) {
    index = Index(map, key, index);
  }
  map->element[index].key = key;
  map->element[index].value = value;
}

RTValue *RTMapGetValueForKey(RTMap *map, RTValue *key) {
  RTInteger32Bit index = Index(map, key, 0);
  while (map->element[index].key != NULL && !RTValueEqual(key, map->element[index].key)) {
    index = Index(map, key, index);
  }
  return map->element[index].value;
}

RTInteger64Bit RTMapHash(RTMap *map) {
  return map->length;
}

bool RTMapEqual(RTMap *map, RTMap *other) {
  if (map->length != other->length) {
    return false;
  }
  for (RTInteger32Bit index = 0; index < map->length; index += 1) {
    RTValue *mapKey = map->element[index].key;
    if (mapKey != NULL) {
      RTValue *mapValue = RTMapGetValueForKey(map, mapKey);
      RTValue *otherValue = RTMapGetValueForKey(other, mapKey);
      if (otherValue == NULL || RTValueEqual(mapValue, otherValue)) return false;
    }
  }
  return true;
}

void RTMapEnumerateKeys(RTMap *map, RTBlock *block) {
  for (RTInteger32Bit index = 0; index < map->length; index += 1) {
    block(map->element[index].key);
  }
}

void RTMapEnumerateValues(RTMap *map, RTBlock *block) {
  for (RTInteger32Bit index = 0; index < map->length; index += 1) {
    block(map->element[index].value);
  }
}