#include "map.h"

typedef struct {
    VALUE *key;
    VALUE *value;
} Pair;

struct Map {
    Type *type;
    Integer32 count;
    Pair pairs[];
};

static Map *MapCreate(Integer32 count, VALUE **error) {
    Map *map = MemoryAlloc(sizeof(Map) + sizeof(Pair) * count, error);
    if (*error != NULL) {
        return NULL;
    }
    map->type = TypeMap;
    map->count = count;
    return map;
} 

VALUE *MapDecode(Byte **bytes, VALUE **error) {
    Integer32 count = DecodeInteger32VLE(bytes);
    Map *map = MapCreate(count, error);
    if (*error != NULL) {
        goto returnError;
    }
    for (Integer32 index = 0; index < count; index += 1) {
        map->pairs[index].key = DecodeValue(bytes, error);
        if (*error != NULL) {
            goto deallocMap;
        }
        map->pairs[index].value = DecodeValue(bytes, error);
        if (*error != NULL) {
            goto deallocMap;
        }
    }
    return BridgeFromMap(map);

deallocMap:
    MemoryDealloc(map);
returnError:
    return NULL;
}

void MapDealloc(VALUE *mapValue) {
    MemoryDealloc(mapValue);
}

Integer64 MapHash(VALUE *mapValue) {
    return BridgeToMap(mapValue)->count;
}
