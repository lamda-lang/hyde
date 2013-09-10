#include <builtin/type.h>

typedef struct Type Type;

struct Type {
    Integer32 count;
    Value *members[];
}; 

Value *TypeCreate(Integer32 count) {
    Type *type = MemoryAlloc(sizeof(Type) + sizeof(Value *) * count);
    if (type == NULL)
        return NULL;
    type->count = count;
    return type;
}

Value *TypeDecode(Byte **bytes) {
    Integer32 count = DecodeInteger32(bytes);
    Type *type = TypeCreate(count);
    if (type == NULL)
        return NULL;
    for (Integer32 index = 0; index < count; index += 1) {
        Value *value = DecodeValue(bytes);
        if (value == NULL)
            return TypeRelease(type), NULL;
        type->members[index] = value;
    }
    return ValueCreate(ModelType, type);
}

void TypeRelease(void *typeData) {
    MemoryDealloc(typeData);
}

Bool TypeEqual(void *typeData, void *otherData) {
    Type *type = typeData;
    Type *other = otherData;
    if (type->count != other->count)
        return FALSE;
    for (Integer32 index = 0; index < type->cpunt; index += 1) 
        if (!ValueEqual(type->members[index], other->members[index])
            return FALSE;
    return TRUE;
}
