#include "map.h"

typedef struct {
    VALUE *key;
    VALUE *value;
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

static Map *Create(Integer32 count, VALUE **error) {
    Map *map = MemoryAlloc(sizeof(Map) + sizeof(Pair) * count, error);
    if (map == NULL) {
        goto returnVALUE;
    }
    map->type = TypeMap;
    map->count = count;
    return map;

returnVALUE:
    return NULL;
}

VALUE *MapCreate(Integer32 count, VALUE **error) {
    Map *map = Create(count, error);
    return BridgeFromMap(map);
}

void *MapDecode(Byte **bytes, VALUE **error) {
    Integer32 count = DecodeInteger32VLE(bytes);
    Model *model = MemoryAlloc(sizeof(Model) + sizeof(Index) * count, error);
    if (model == NULL) {
        goto returnVALUE;
    }
    model->count = count;
    for (Integer32 index = 0; index < count; index += 1) {
        model->pair[index].key = DecodeInteger32VLE(bytes);
        model->pair[index].value = DecodeInteger32VLE(bytes);
    }
    return model;

returnVALUE:
    return NULL;
}

void MapDealloc(VALUE *mapVALUE) {
    MemoryDealloc(mapVALUE);
}

Integer64 MapHash(VALUE *mapVALUE) {
    return BridgeToMap(mapVALUE)->count;
}

void MapEnumerate(VALUE *mapVALUE, void (*callback)(VALUE *value)) {
    Map *map = BridgeToMap(mapVALUE);
    for (Integer32 index = 0; index < map->count; index += 1) {
        callback(map->pair[index].key);
        callback(map->pair[index].value);
    }
}

VALUE *MapGetVALUEForKey(VALUE *mapVALUE, VALUE *key) {
    return NULL;
}
