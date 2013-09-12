#include <builtin/do.h>

typedef struct Do Do;

struct Do {
  Integer32 count;
  Value *values[];
};

static Do *DoCreate(Integer32 count) {
    Do *block = MemoryAlloc(sizeof(Do) * sizeof(Value *) * count);
    if (block == NULL)
        return NULL;
    block->count = count;
    return block;
}

Value *DoDecode(Byte **bytes) {
    Integer32 count = DecodeInteger32(bytes);
    Do *block = DoCreate(count);
    if (block == NULL)
        return NULL;
    for (Integer32 index = 0; index < count; index += 1) {
        Value *value = ValueDecode(bytes);
        if (value == NULL)
            return DoRelase(block), NULL;
        block->values[index] = value;
    }
    return ValueCreate(ModelDo, block);
}

void DoRelase(void *doData) {
    MemoryDealloc(doData);
}

Bool DoEqual(void *doData, void *otherData) {
    Do *block = doData;
    Do *other = otherData;
    if (block->count != other->count)
        return FALSE;
    for (Integer32 index = 0; index < block->count; index += 1)
        if (!ValueEqual(block->values[index], other->values[index]))
            return FALSE;
    return TRUE;
}
