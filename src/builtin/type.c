#include <builtin/type.h>

typedef struct Type Type;

struct Type {
    Value *type;
    Integer32 count;
    Value *members[];
}; 

Value *TypeCreate(Integer32 count, Error *error) {
    Type *type = MemoryAlloc(sizeof(Type) + sizeof(Value *) * count, error);
    if (*error != ErrorNone)
        return NULL;
    type->type = NULL;
    type->count = count;
    return type;
}

Value *TypeDecode(Byte **bytes, Error *error) {
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

void TypeDealloc(Value *typeValue) {
    MemoryDealloc(typeValue);
}
