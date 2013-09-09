#include <builtin/map.h>

typedef struct Map Map;
typedef struct Pair Pair;

struct Pair {
    Value *key;
    Value *value;
};

struct Map {
    Value value;
    Integer32 count;
    Pair pairs[];
};

static Map *MapCreate(Integer32 count, Error *error) {
    Map *map = MemoryAlloc(sizeof(Map) + sizeof(Pair) * count, error);
    if (*error != ErrorNone)
        return NULL;
    map->value = ValueMap;
    map->count = count;
    return map;
} 

static Map *MapDealloc(Map *map) {
    MemoryDealloc(map);
    return NULL;
}

Value *MapDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32(bytes);
    Map *map = MapCreate(count, error);
    if (*error != ErrorNone)
        return MapDealloc(map);
    for (Integer32 index = 0; index < count; index += 1) {
        map->pairs[index].key = DecodeValue(bytes, error);
        if (*error != ErrorNone)
            return MapDealloc(map);
        map->pairs[index].value = DecodeValue(bytes, error);
        if (*error != ErrorNone)
            return MapDealloc(map);
    }
    return map;
}

void MapRelease(Value *mapValue) {
    Map *map = mapValue;
    MapDealloc(map);
}
