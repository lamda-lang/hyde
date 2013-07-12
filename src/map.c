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
    Value base;
    Integer32 count;
    Pair pair[];
};

typedef struct {
    Integer32 count;
    Index pair[];
} Model;

static Map *Create(Integer32 count, Error *error) {
    Map *map = MemoryAlloc(sizeof(Map) + sizeof(Pair) * count, error);
    if (map == NULL) {
        goto returnError;
    }
    map->base = TypeMap;
    map->count = count;
    return map;

returnError:
    return NULL;
}

Value *MapCreate(Integer32 count, Error *error) {
    Map *map = Create(count, error);
    return BridgeFromMap(map);
}

void *MapDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32VLE(bytes);
    Model *model = MemoryAlloc(sizeof(Model) + sizeof(Index) * count, error);
    if (model == NULL) {
        goto returnError;
    }
    model->count = count;
    for (Integer32 index = 0; index < count; index += 1) {
        model->pair[index].key = DecodeInteger32VLE(bytes);
        model->pair[index].value = DecodeInteger32VLE(bytes);
    }
    return model;

returnError:
    return NULL;
}

Value *MapEval(void *data, Code *code, Value **context, bool pure, Error *error) {
    Model *model = data;
    Map *map = Create(model->count, error);
    if (map == NULL) {
        goto returnError;
    }
    Value *mapValue = BridgeFromMap(map);
    for (Integer32 index = 0; index < model->count; index += 1) {
        Value *key = CodeEvalInstructionAtIndex(code, context, model->pair[index].key, true, error);
        if (key == NULL) {
            goto deallocMap;
        }
        Value *value = CodeEvalInstructionAtIndex(code, context, model->pair[index].value, true, error);
        if (value == NULL) {
            goto deallocMap;
        }
        map->pair[index].key = key;
        map->pair[index].value = value;
    }
    return mapValue;

deallocMap:
    MapDealloc(mapValue);
returnError:
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
    Map *map = BridgeToMap(mapValue);
    for (Integer32 index = 0; index < map->count; index += 1) {
        if (ValueEqual(key, map->pair[index].key)) {
            return map->pair[index].value;
        }
    }
    return NULL;
}
