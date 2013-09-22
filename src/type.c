#include "type.h"

struct Type {
    Integer32 count;
    Value *members[];
}; 

static Size TypeSize(Integer32 count) {
    return sizeof(Type) + sizeof(Value *) * count;
}

static Type *TypeCreate(Integer32 count, Error *error) {
    Size size = TypeSize(count);
    Type *type = MemoryAlloc(size, error);
    if (ERROR(error))
        return NULL;
    type->count = count;
    return type;
}

Type *TypeDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32(bytes);
    Type *type = TypeCreate(count, error);
    if (ERROR(error))
        return NULL;
    for (Integer32 index = 0; index < count; index += 1) {
        type->members[index] = ValueDecode(bytes, error);
        if (ERROR(error))
            goto type;
    }
    return type;

type:
    TypeRelease(type);
    return NULL;
}

Bool TypeEqual(Type *type, Type *other) {
    if (type->count != other->count)
        return FALSE;
    for (Integer32 index = 0; index < type->count; index += 1) 
        if (!ValueEqual(type->members[index], other->members[index]))
            return FALSE;
    return TRUE;
}

Size TypeRelease(Type *type) {
    Size size = TypeSize(type->count);
    MemoryDealloc(type);
    return size;
}
