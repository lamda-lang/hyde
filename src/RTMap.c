#include "RTMap.h"

struct RTElement {
  RTValue key;
  RTValue value;
};

struct RTMap {
  RTBase base;
  RTInteger32Bit length;
  struct RTElement element[];
};

static inline RTInteger32Bit RTMapIndex(RTMap map, RTValue value, RTInteger32Bit offset) {
  /* missing */
  map = NULL;
  value = NULL;
  offset = 0;
  return 0;
}

RTValue RTMapValueBridge(RTMap map) {
  return (RTValue)map;
}

RTMap RTMapDecode(RTByte **data) {
  RTInteger32Bit length = RTDecodeVBRInteger32Bit(data) * 2;
  RTSize size = sizeof(struct RTMap) + sizeof(struct RTElement) * length;
  RTMap map = RTMemoryAlloc(size);
  if (map == NULL) {
    return NULL;
  }
  map->base = RTBaseInit(RTTypeMap, RTFlagNone);
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
  /* missing */
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
      /* missing */
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
