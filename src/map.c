#include "map.h"

typedef struct {
    Value *key;
    Value *value;
} Pair;

struct Map {
    Integer32 count;
    Pair pairs[];
};

static Map *MapCreate(Integer32 count) {
    Map *map = MemoryAllocRegion(sizeof(Map), sizeof(Pair), count);
    map->count = count;
    return map;
}

static void MapDealloc(Map *map) {
    MemoryDealloc(map);
}

Value *MapDecode(Binary *binary, Integer32 *offset) {
    Integer32 count;
    if (!BinaryDecodeInteger32(binary, offset, &count))
        return NULL;
    Map *map = MapCreate(count);
    for (Integer32 index = 0; index < count; index += 1) {
        Value *key = BinaryDecodeValue(binary, offset);
        if (key == NULL)
            goto out;
        Value *value = BinaryDecodeValue(binary, offset);
        if (value == NULL)
            goto out;
        map->pairs[index].key = key;
        map->pairs[index].value = value;
    }
    return ValueCreateMap(map);

out:
    MapDealloc(map);
    return NULL;
}
