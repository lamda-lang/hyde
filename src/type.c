#include "type.h"

typedef struct Type Type;

struct Type {
    VALUE *type;
    Integer32 count;
    VALUE *members[];
}; 

VALUE *TypeCreate(Integer32 count, Error *error) {
    Type *type = MemoryAlloc(sizeof(Type) + sizeof(VALUE *) * count, error);
    if (*error != ErrorNone) return NULL;
    type->type = NULL;
    type->count = count;
    return type;
}

VALUE *TypeBootstrap(Error *error) {
    Type *type = MemoryAlloc(sizeof(Type), error);
    if (*error != ErrorNone) return NULL;
    type->type = NULL;
    type->count = 0;
    return type;
}

VALUE *TypeDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32(bytes);
    Type *type = TypeCreate(count, error);
    if (*error != ErrorNone) goto returnError;
    for (Integer32 index = 0; index < count; index += 1) {
        type->members[index] = DecodeValue(bytes, error);
        if (*error != ErrorNone) goto deallocType;
    }
    return type;

deallocType:
    MemoryDealloc(type);
returnError:
    return NULL;
}

void TypeDealloc(VALUE *typeValue) {
    MemoryDealloc(typeValue);
}
