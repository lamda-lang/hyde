#include "map.h"

struct Element {
  Value *key;
  Value *value;
};

struct Map {
  Value base;
  Integer32Bit length;
  struct Element element[];
};

static inline Integer32Bit MapIndex(Map *map, Value *value, Integer32Bit offset) {
  return (ValueHash(value) + offset) % map->length;
}

Value *MapValueBridge(Map *map) {
  return (Value *)map;
}

Map *MapDecode(Byte **data) {
  Integer32Bit length = DecodeVBRInteger32Bit(data) * 2;
  Size size = sizeof(struct Map) + sizeof(struct Element) * length;
  Map *map = MemoryAlloc(size);
  if (map == NULL) {
    goto error;
  }
  map->base = ValueInit(TypeMap, FlagNone);
  map->length = length;
  for (Integer32Bit index = 0; index < length; index += 1) {
    map->element[index].key = NULL;
    map->element[index].value = NULL;
  }
  return map;

error:
  return NULL;
}

void MapDealloc(Value *map) {
  MemoryDealloc(map);
}

void MapSetValueForKey(Map *map, Value *value, Value *key) {
  Integer32Bit index = MapIndex(map, key, 0);
  while (map->element[index].key != NULL) {
    index = MapIndex(map, key, index);
  }
  map->element[index].key = key;
  map->element[index].value = value;
}

Integer64Bit MapHash(Value *map_Map) {
  Map *map = ValueMapBridge(map_Map);
  return map->length;
}

void MapEnumerate(Value *map_Map, void (*block)(Value *value)) {
  Map *map = ValueMapBridge(map_Map);
  for (Integer32Bit index = 0; index < map->length; index += 1) {
    block(map->element[index].key);
    block(map->element[index].value);
  }
}
