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
    goto error;
  }
  map->base = RTValueInit(RTTypeMap, RTFlagNone);
  map->length = length;
  for (RTInteger32Bit index = 0; index < length; index += 1) {
    map->element[index].key = NULL;
    map->element[index].value = NULL;
  }
  return map;

error:
  return NULL;
}

void RTMapDealloc(RTValue *map) {
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

RTInteger64Bit RTMapHash(RTValue *map_RTMap) {
  RTMap *map = RTValueMapBridge(map_RTMap);
  return map->length;
}

void RTMapEnumerate(RTValue *map_RTMap, RTBlock *block) {
  RTMap *map = RTValueMapBridge(map_RTMap);
  for (RTInteger32Bit index = 0; index < map->length; index += 1) {
    block(map->element[index].key);
    block(map->element[index].value);
  }
}
