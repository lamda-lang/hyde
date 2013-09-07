#include <builtin/map.h>

typedef struct Map Map;
typedef struct Pair Pair;

struct Pair {
    VALUE *key;
    VALUE *value;
};

struct Map {
    VALUE *type;
    Integer32 count;
    Pair pairs[];
};

static Map *MapCreate(Integer32 count, Error *error) {
    Map *map = MemoryAlloc(sizeof(Map) + sizeof(Pair) * count, error);
    if (*error != ErrorNone) return NULL;
    map->type = RuntimeValueForConstant(ConstantMapType);
    map->count = count;
    return map;
} 

VALUE *MapDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32(bytes);
    Map *map = MapCreate(count, error);
    if (*error != ErrorNone) goto returnError;
    for (Integer32 index = 0; index < count; index += 1) {
        map->pairs[index].key = DecodeValue(bytes, error);
        if (*error != ErrorNone) goto deallocMap;
        map->pairs[index].value = DecodeValue(bytes, error);
        if (*error != ErrorNone) goto deallocMap;
    }
    return map;

deallocMap:
    MemoryDealloc(map);
returnError:
    return NULL;
}

void MapDealloc(VALUE *mapValue) {
    MemoryDealloc(mapValue);
}
