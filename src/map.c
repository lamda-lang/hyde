#include "map.h"

typedef struct {
    Value *key;
    Value *value;
} Pair;

typedef struct {
    Integer32 key;
    Integer32 value;
} Index;

struct Map {
    Type *type;
    Integer32 count;
    Pair pair[];
};

typedef struct {
    Integer32 count;
    Index pair[];
} Model;

static Map *Create(Integer32 count, Value **error) {
    Map *map = MemoryAlloc(sizeof(Map) + sizeof(Pair) * count, error);
    if (map == NULL) {
        goto returnValue;
    }
    map->type = TypeMap;
    map->count = count;
    return map;

returnValue:
    return NULL;
}

Value *MapCreate(Integer32 count, Value **error) {
    Map *map = Create(count, error);
    return BridgeFromMap(map);
}

void *MapDecode(Byte **bytes, Value **error) {
    Integer32 count = DecodeInteger32VLE(bytes);
    Model *model = MemoryAlloc(sizeof(Model) + sizeof(Index) * count, error);
    if (model == NULL) {
        goto returnValue;
    }
    model->count = count;
    for (Integer32 index = 0; index < count; index += 1) {
        model->pair[index].key = DecodeInteger32VLE(bytes);
        model->pair[index].value = DecodeInteger32VLE(bytes);
    }
    return model;

returnValue:
    return NULL;
}

void MapDealloc(Value *mapValue) {
    MemoryDealloc(mapValue);
}

Integer64 MapHash(Value *mapValue) {
    return BridgeToMap(mapValue)->count;
}

void MapEnumerate(Value *mapValue, void (*callback)(Value *value)) {
    Map *map = BridgeToMap(mapValue);
    for (Integer32 index = 0; index < map->count; index += 1) {
        callback(map->pair[index].key);
        callback(map->pair[index].value);
    }
}

Value *MapGetValueForKey(Value *mapValue, Value *key) {
    return NULL;
}
