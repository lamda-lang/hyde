#include <builtin/map.h>

typedef struct Pair Pair;

struct Pair {
    Value *key;
    Value *value;
};

struct Map {
    Integer32 count;
    Pair pairs[];
};

static Map *MapCreate(Integer32 count) {
    Map *map = MemoryAlloc(sizeof(Map) + sizeof(Pair) * count);
    if (map == NULL)
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

Value *MapDecode(Byte **bytes) {
    Integer32 count = DecodeInteger32(bytes);
    Map *map = MapCreate(count);
    if (map == NULL)
        return NULL;
    for (Integer32 index = 0; index < count; index += 1) {
        Value *key = ValueDecode(bytes);
        if (key == NULL)
            return MapRelease(map), NULL;
        Value *value = ValueDecode(bytes);
        if (value == NULL)
            return MapRelease(map), NULL;
        map->pairs[index].key = key;
        map->pairs[index].value = value;
    }
    return ValueCreate(MODEL_MAP, map);
}

Value *MapEval(Map *map, Value *context) {
    Map *new = MapCreate(map->count);
    if (new == NULL)
        return NULL;
    for (Integer32 index = 0; index < map->count; index += 1) {
        Value *key = ValueEval(map->pairs[index].key, context);
        if (key == NULL)
            return MapRelease(new), NULL;
        Value *value = ValueEval(map->pairs[index].value, context);
        if (value == NULL)
            return MapRelease(new), NULL;
        new->pairs[index].key = key;
        new->pairs[index].value = value;
    }
    return ValueCreate(MODEL_MAP, new);
}

Value *MapEqual(Map *map, Map *other) {
    if (map->count != other->count)
        return VALUE_FALSE;
    for (Integer32 index = 0; index < map->count; index += 1) {
        Value *value = MapValueForKey(other, map->pairs[index].key);
        if (value == NULL || ValueEqual(value, map->pairs[index].value) == VALUE_FALSE)
            return VALUE_FALSE;
    }
    return VALUE_TRUE;
}

Size MapRelease(Map *map) {
    Integer32 count = map->count;
    MemoryDealloc(map);
    return sizeof(Map) + sizeof(Pair) * count;
}
