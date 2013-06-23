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
    Integer32 length;
    Pair pair[];
};

typedef struct {
    Integer32 count;
    Index index[];
} Model;


static Integer32 IndexForKey(Map *map, Value *value, Integer32 offset) {
    return (ValueHash(value) + offset) % map->length;
}

static void SetValueForKey(Map *map, Value *value, Value *key) {
    Integer32 index = IndexForKey(map, key, 0);
    while (map->pair[index].key != NULL) {
        index = IndexForKey(map, key, index);
    }
    map->pair[index].key = key;
    map->pair[index].value = value;
}

static Map *Create(Integer32 length, Error *error) {
    Map *map = MemoryAlloc(sizeof(Map) + sizeof(Pair) * length, error);
    if (map == NULL) {
        goto returnError;
    }
    map->base = TypeMap;
    map->length = length;
    for (Integer32 index = 0; index < length; index += 1) {
	map->pair[index].key = NULL;
	map->pair[index].value = NULL;
    }
    return map;

returnError:
    return NULL;
}

void *MapDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32VLE(bytes);
    Model *model = MemoryAlloc(sizeof(Model) + sizeof(Index) * count, error);
    if (model == NULL) {
	goto returnError;
    }
    model->count = count;
    for (Integer32 index = 0; index < count; index += 1) {
	model->index[index].key = DecodeInteger32VLE(bytes);
	model->index[index].value = DecodeInteger32VLE(bytes);
    }
    return model;

returnError:
    return NULL;
}

Value *MapEval(void *data, Code *code, bool pure, Error *error) {
    Model *model = data;
    Map *map = Create(model->count * 2, error);
    if (map == NULL) {
	goto returnError;
    }
    Value *mapValue = BridgeFromMap(map);
    for (Integer32 index = 0; index < model->count; index += 1) {
	Value *key = CodeEvalInstructionAtIndex(code, model->index[index].key, true, error);
	if (key == NULL) {
	    goto deallocMap;
	}
	Value *value = CodeEvalInstructionAtIndex(code, model->index[index].value, true, error);
	if (value == NULL) {
	    goto deallocMap;
	}
	SetValueForKey(map, value, key);
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
    return BridgeToMap(mapValue)->length;
}

void MapEnumerate(Value *mapValue, void (*callback)(Value *value)) {
    Map *map = BridgeToMap(mapValue);
    for (Integer32 index = 0; index < map->length; index += 1) {
        callback(map->pair[index].key);
        callback(map->pair[index].value);
    }
}

Value *MapGetValueForKey(Value *mapValue, Value *key) {
    Map *map = BridgeToMap(mapValue);
    Integer32 index = IndexForKey(map, key, 0);
    while (map->pair[index].key != NULL && !ValueEqual(key, map->pair[index].key)) {
        index = IndexForKey(map, key, index);
    }
    return map->pair[index].value;
}
