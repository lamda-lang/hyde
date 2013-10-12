#include "type.h"

struct Type {
    Integer32 count;
    Value *members[];
}; 

static Type *TypeCreate(Integer32 count) {
    Type *type = MemoryAllocRegion(sizeof(Type), sizeof(Value *), count);
    type->count = count;
    return type;
}

static void TypeDealloc(Type *type) {
    MemoryDealloc(type);
}

Value *TypeDecodePrimitive(Binary *binary, Integer32 *offset) {
    Integer32 count;
    if (!BinaryDecodeInteger32(binary, offset, &count))
        return NULL;
    Type *type = TypeCreate(count);
    for (Integer32 index = 0; index < count; index += 1) {
        Value *member = BinaryDecodeValue(binary, offset);
        if (member == NULL)
            goto out;
        type->members[index] = member;
    }
    return ValueCreateType(type);

out:
    TypeDealloc(type);
    return NULL;
}
