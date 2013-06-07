#include "map.h"

typedef struct {
    Element key;
    Element value;
} Pair;

struct Map {
    Value base;
    Integer32 capacity;
    Pair pair[];
};

static Integer32 IndexForValue(Map *map, Value *value, Integer32 offset) {
    return (ValueHash(value) + offset) % map->capacity;
}

static void SetValueForKey(Map *map, Value *value, Value *key) {
    Integer32 index = IndexForValue(map, key, 0);
    while (map->pair[index].key.value != NULL) {
        index = IndexForValue(map, key, index);
    }
    map->pair[index].key.value = key;
    map->pair[index].value.value = value;
}

static Map *Create(Integer32 count, Error *error) {
    Integer32 capacity = count << 1;
    Size size = sizeof(Map) + sizeof(Element) * capacity;
    Map *map = MemoryAlloc(size, error);
    if (map == NULL) {
        goto returnError;
    }
    map->base = TypeMap;
    map->capacity = capacity;
    return map;

returnError:
    return NULL;
}

Value *MapValueBridge(Map *map) {
    return (Value *)map;
}

Value *MapDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32VLE(bytes);
    Map *map = Create(count, error);
    if (map == NULL) {
	goto returnError;
    }
    for (Integer32 index = 0; index < count; index += 1) {
	map->pair[index].key.index = DecodeInteger32VLE(bytes);
	map->pair[index].value.index = DecodeInteger32VLE(bytes);
    }
    return MapValueBridge(map);

returnError:
    return NULL;
}

void MapFetch(Value *mapValue, Value **values) {
    Map *map = ValueMapBridge(mapValue, NULL);
    Integer32 count = map->capacity >> 1;
    Pair pair[count];
    Size size = sizeof(pair);
    MemoryCopy(map->pair, pair, size);
    for (Integer32 index = 0; index < map->capacity; index += 1) {
	map->pair[index].key.value = NULL;
	map->pair[index].value.value = NULL;
    }
    for (Integer32 index = 0; index < count; index += 1) {
        Integer32 keyIndex = pair[index].key.index;
	Integer32 valueIndex = pair[index].value.index;
        SetValueForKey(map, values[valueIndex], values[keyIndex]);
    }
}

void MapDealloc(Value *mapValue) {
    MemoryDealloc(mapValue);
}

Integer64 MapHash(Value *mapValue) {
    return ValueMapBridge(mapValue, NULL)->capacity;
}

void MapEnumerate(Value *mapValue, void (*callback)(Value *value)) {
    Map *map = ValueMapBridge(mapValue, NULL);
    for (Integer32 index = 0; index < map->capacity; index += 1) {
        callback(map->pair[index].key.value);
        callback(map->pair[index].value.value);
    }
}
