#include "map.h"

typedef struct {
    Value *key;
    Value *value;
} Element;

struct Map {
    Value base;
    Integer32 length;
    Element element[];
};

static inline Integer32 IndexForValue(Map *map, Value *value, Integer32 offset) {
    return (ValueHash(value) + offset) % map->length;
}

static inline void SetValueForKey(Map *map, Value *value, Value *key) {
    Integer32 index = IndexForValue(map, key, 0);
    while (map->element[index].key != NULL) {
        index = IndexForValue(map, key, index);
    }
    map->element[index].key = key;
    map->element[index].value = value;
}

static inline Map *Create(Integer32 count, Error *error) {
    Integer32 length = count << 1;
    Size size = sizeof(Map) + sizeof(Element) * length;
    Map *map = MemoryAlloc(size, error);
    if (map == NULL) {
        goto returnError;
    }
    map->base = TypeMap;
    map->length = length;
    for (Integer32 index = 0; index < length; index += 1) {
        map->element[index].key = NULL;
        map->element[index].value = NULL;
    }
    return map;

returnError:
    return NULL;
}

Value *MapValueBridge(Map *map) {
    return (Value *)map;
}

Map *MapDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32VLE(bytes);
    return Create(count, error);
}

void MapFetch(Map *map, Value **values, Byte **bytes) {
    Integer32 count = map->length >> 1;
    for (Integer32 index = 0; index < count; index += 1) {
	Integer32 keyIndex = DecodeInteger32VLE(bytes);
	Integer32 valueIndex = DecodeInteger32VLE(bytes);
	Value *key = values[keyIndex];
	Value *value = values[valueIndex];
	SetValueForKey(map, value, key);
    }
}

void MapDealloc(Value *mapValue) {
    MemoryDealloc(mapValue);
}

Integer64 MapHash(Value *mapValue) {
    Map *map = ValueMapBridge(mapValue);
    return map->length;
}

void MapEnumerate(Value *mapValue, void (*block)(Value *value)) {
    Map *map = ValueMapBridge(mapValue);
    for (Integer32 index = 0; index < map->length; index += 1) {
        block(map->element[index].key);
        block(map->element[index].value);
    }
}
