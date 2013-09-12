#include <builtin/lamda.h>

typedef struct Lamda Lamda;

struct Lamda {
    Integer8 arity;
    Integer8 count;
    Value *result;
    Value *upvalues[];
};

static Lamda *LamdaCreate(Value *result, Integer8 arity, Integer8 count) {
    Lamda *lamda = MemoryAlloc(sizeof(Lamda) + sizeof(Value *) * count);
    if (lamda == NULL)
        return NULL;
    lamda->arity = arity;
    lamda->count = count;
    lamda->result = result;
    return lamda;
}

Value *LamdaDecode(Byte **bytes) {
    Integer8 arity = DecodeInteger8(bytes);
    Value *result = ValueDecode(bytes);
    if (result == NULL)
        return NULL;
    Integer8 count = DecodeInteger8(bytes);
    Lamda *lamda = LamdaCreate(result, arity, count);
    if (lamda == NULL)
        return NULL;
    for (Integer8 index = 0; index < count; index += 1) {
        Value *upvalue = ValueDecode(bytes);
        if (upvalue == NULL)
            return LamdaRelease(lamda), NULL;
        lamda->upvalues[index] = upvalue;
    }
    return ValueCreate(ModelLamda, lamda);
}

void LamdaRelease(void *lamdaData) {
    MemoryDealloc(lamdaData);
}

Bool LamdaEqual(void *lamdaData, void *otherData) {
    Lamda *lamda = lamdaData;
    Lamda *other = otherData;
    if (lamda->arity != other->arity)
        return FALSE;
    if (lamda->count != other->count)
        return FALSE;
    if (!ValueEqual(lamda->result, other->result))
        return FALSE;
    for (Integer8 index = 0; index < lamda->count; index += 1)
        if (!ValueEqual(lamda->upvalues[index], other->upvalues[index]))
            return NULL;
    return TRUE;
}
