#include <builtin/do.h>

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
    return ValueCreate(MODEL_DO, block);
}

void DoRelase(Do *block) {
    MemoryDealloc(block);
}

Bool DoEqual(Do *block, Do *other) {
    if (block->count != other->count)
        return FALSE;
    for (Integer32 index = 0; index < block->count; index += 1)
        if (!ValueEqual(block->values[index], other->values[index]))
            return FALSE;
    return TRUE;
}
