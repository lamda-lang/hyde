#include "map.h"

typedef struct Pair Pair;

struct Pair {
    Value *key;
    Value *value;
};

struct Map {
    Integer32 count;
    Pair pairs[];
};

static Size MapSizeOf(Integer32 count) {
    return sizeof(Map) + sizeof(Pair) * count;
}

static Map *MapCreate(Integer32 count, Error *error) {
    Size size = MapSizeOf(count);
    Map *map = MemoryAlloc(size, error);
    if (ERROR(error))
        return NULL;
    map->count = count;
    return map;
} 

static Value *MapValueForKey(Map *map, Value *key) {
    for (Integer32 index = 0; index < map->count; index += 1)
        if (ValueEqual(key, map->pairs[index].key))
            return map->pairs[index].value;
    return NULL;
}

Size MapSize(Map *map) {
    Size size = INTEGER_32_SIZE;
    for (Integer32 index = 0; index < map->count; index += 1) {
        size += ValueSize(map->pairs[index].key);
        size += ValueSize(map->pairs[index].value);
    }
    return size;
}

Size MapEncode(Map *map, Byte **bytes) {
    EncodeInteger32(map->count, bytes);
    for (Integer32 index = 0; index < map->count; index += 1) {
        ValueEncode(map->pairs[index].key, bytes);
        ValueEncode(map->pairs[index].value, bytes);
    }
    return MapSize(map);
}

Map *MapDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32(bytes);
    Map *map = MapCreate(count, error);
    if (ERROR(error))
        return NULL;
    for (Integer32 index = 0; index < count; index += 1) {
        map->pairs[index].key = ValueDecode(bytes, error);
        if (ERROR(error))
            goto map;
        map->pairs[index].value = ValueDecode(bytes, error);
        if (ERROR(error))
            goto map;
    }
    return map;

map:
    MapRelease(map);
    return NULL;
}

Value *MapEval(Value *value, Map *map, Value *context, Error *error) {
    Map *new = MapCreate(map->count, error);
    if (ERROR(error))
        return NULL;
    for (Integer32 index = 0; index < map->count; index += 1) {
        new->pairs[index].key = ValueEval(map->pairs[index].key, context, error);
        if (ERROR(error))
            goto new;
        new->pairs[index].value = ValueEval(map->pairs[index].value, context, error);
        if (ERROR(error))
            goto new;
    }
    return ValueMap(new, error);

new:
    MapRelease(map);
    return NULL;
}

Bool MapEqual(Map *map, Map *other) {
    if (map->count != other->count)
        return FALSE;
    for (Integer32 index = 0; index < map->count; index += 1) {
        Value *value = MapValueForKey(other, map->pairs[index].key);
        if (value == NULL || !ValueEqual(value, map->pairs[index].value))
            return FALSE;
    }
    return TRUE;
}

Size MapRelease(Map *map) {
    Size size = MapSizeOf(map->count);
    MemoryDealloc(map);
    return size;
}
