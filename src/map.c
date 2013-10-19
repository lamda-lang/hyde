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

Bool MapDecode(Binary *binary, Integer32 *offset, Value **value) {
    Integer32 count;
    if (!BinaryDecodeInteger32(binary, offset, &count))
        return FALSE;
    Map *map = MapCreate(count);
    for (Integer32 index = 0; index < count; index += 1) {
        Value *key;
        Value *value;
        if (!BinaryDecodeValue(binary, offset, &key))
            goto out;
        if (!BinaryDecodeValue(binary, offset, &value))
            goto out;
        map->pairs[index].key = key;
        map->pairs[index].value = value;
    }
    *value = ValueCreateMap(map);
    return TRUE;

out:
    MapDealloc(map);
    return FALSE;
}

Bool MapEval(Map *map, Context *context, Stack *stack) {
    Map *eval = MapCreate(map->count);
    for (Integer32 index = 0; index < map->count; index += 1) {
        if (!ValueEval(map->pairs[index].key, context, stack))
            goto out;
        eval->pairs[index].key = StackPopValue(stack);
        if (!ValueEval(map->pairs[index].value, context, stack))
            goto out;
        eval->pairs[index].value = StackPopValue(stack);
    }
    Value *value = ValueCreateMap(eval);
    StackReplaceTop(stack, value);
    return TRUE;

out:
    MapDealloc(eval);
    return FALSE;
}
