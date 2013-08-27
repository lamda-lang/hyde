#include "type.h"

typedef struct {
    VALUE *type;
    Integer32 count;
    VALUE *members[];
} Type;

static Type *TypeCreate(Integer32 count, VALUE **error) {
    Type *type = MemoryAlloc(sizeof(Type) + sizeof(VALUE *) * count, error);
    if (*error != NULL) {
        return NULL;
    }
    type->type = RuntimeTypeType;
    type->count = count;
    return type;
}

VALUE *TypeDecode(Byte **bytes, VALUE **error) {
    Integer32 count = DecodeInteger32VLE(bytes);
    Type *type = TypeCreate(count, error);
    if (*error != NULL) {
        goto returnError;
    }
    for (Integer32 index = 0; index < count; index += 1) {
        type->members[index] = DecodeValue(bytes, error);
        if (*error != NULL) {
            goto deallocType;
        }
    }
    return type;

deallocType:
    MemoryDealloc(type);
returnError:
    return NULL;
}
