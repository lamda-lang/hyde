#include "type.h"

struct Type {
    Integer32 count;
    Value *members[];
}; 

static Type *TypeCreate(Integer32 count) {
    Type *type = MemoryAlloc(sizeof(Type) + sizeof(Value *) * count);
    if (type == NULL)
        return NULL;
    type->count = count;
    return type;
}

Type *TypeDecode(Byte **bytes) {
    Integer32 count = DecodeInteger32(bytes);
    Type *type = TypeCreate(count);
    if (type == NULL)
        return NULL;
    for (Integer32 index = 0; index < count; index += 1) {
        Value *value = ValueDecode(bytes);
        if (value == NULL)
            return TypeRelease(type), NULL;
        type->members[index] = value;
    }
    return type;
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
    Integer32 count = type->count;
    MemoryDealloc(type);
    return sizeof(Type) + sizeof(Value *) * count;
}
