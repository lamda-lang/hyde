#include "map.h"

typedef struct {
    Element key;
    Element value;
} Pair;

struct Map {
    Value base;
    Integer32 length;
    Pair *pair;
};

static Integer32 IndexForValue(Integer32 length, Value *value, Integer32 offset) {
    return (ValueHash(value) + offset) % length;
}

static void SetValueForKey(Pair *pair, Integer32 length, Value *value, Value *key) {
    Integer32 index = IndexForValue(length, key, 0);
    while (pair[index].key.value != NULL) {
        index = IndexForValue(length, key, index);
    }
    pair[index].key.value = key;
    pair[index].value.value = value;
}

static Map *Create(Integer32 length, Error *error) {
    Map *map = MemoryAlloc(sizeof(Map), error);
    if (map == NULL) {
        goto returnError;
    }
    Pair *pair = MemoryAlloc(sizeof(Pair) * length, error);
    if (pair == NULL) {
	goto deallocMap;
    }
    map->base = TypeMap;
    map->length = length;
    map->pair = pair;
    return map;

deallocMap:
    MemoryDealloc(map);
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
    Map *map = ValueMapBridge(mapValue);
    for (Integer32 index = 0; index < map->length; index += 1) {
	Integer32 keyIndex = map->pair[index].key.index;
	Integer32 valueIndex = map->pair[index].value.index;
	map->pair[index].key.value = values[keyIndex];
	map->pair[index].value.value = values[valueIndex];
    }
}

void MapDealloc(Value *mapValue) {
    if (mapValue != NULL) {
	Map *map = ValueMapBridge(mapValue);
	MemoryDealloc(map->pair);
	MemoryDealloc(map);
    }
}

Integer64 MapHash(Value *mapValue) {
    return ValueMapBridge(mapValue)->length;
}

void MapEnumerate(Value *mapValue, void (*callback)(Value *value)) {
    Map *map = ValueMapBridge(mapValue);
    for (Integer32 index = 0; index < map->length; index += 1) {
        callback(map->pair[index].key.value);
        callback(map->pair[index].value.value);
    }
}

Value *MapGetValueForKey(Map *map, Value *key) {
    return NULL;
}

Value *MapEval(Value *mapValue, bool pure, Error *error) {
    Map *map = ValueMapBridge(mapValue);
    Integer32 length = map->length << 1;
    Pair *pair = MemoryAlloc(sizeof(Pair) * length, error);
    if (pair == NULL) {
	goto returnError;
    }
    for (Integer32 index = 0; index < length; index += 1) {
	pair[index].key.value = NULL;
	pair[index].value.value = NULL;
    }
    for (Integer32 index = 0; index < map->length; index += 1) {
	Value *key = ValueEval(map->pair[index].key.value, true, error);
	if (key == NULL) {
	    goto deallocPair;
	};
	Value *value = ValueEval(map->pair[index].value.value, true, error);
	if (value == NULL) {
	    goto deallocPair;
	};
        SetValueForKey(pair, length, value, key);
    }
    MemoryDealloc(map->pair);
    map->length = length;
    map->pair = pair;
    return mapValue;

deallocPair:
    for (Integer32 index = 0; index < length; index += 1) {
	ValueDealloc(pair[index].key.value);
	ValueDealloc(pair[index].value.value);
    }
    MemoryDealloc(pair);
returnError:
    return NULL;
}
