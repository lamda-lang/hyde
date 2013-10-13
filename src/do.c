#include "do.h"

typedef struct {
    Value *name;
    Value *value;
} Statement;

struct Do {
  Integer32 count;
  Statement statements[];
};

static Do *DoCreate(Integer32 count) {
    Do *block = MemoryAllocRegion(sizeof(Do), sizeof(Statement), count);
    block->count = count;
    return block;
}

static void DoDealloc(Do *block) {
    MemoryDealloc(block);
}

Value *DoDecode(Binary *binary, Integer32 *offset) {
    Integer32 count;
    if (!BinaryDecodeInteger32(binary, offset, &count))
        return NULL;
    Do *block = DoCreate(count);
    for (Integer32 index = 0; index < count; index += 1) {
        Value *name = BinaryDecodeValue(binary, offset);
        if (name == NULL)
            goto out;
        Value *value = BinaryDecodeValue(binary, offset);
        if (value == NULL)
            goto out;
        block->statements[index].name = name;
        block->statements[index].value = value;
    }
    return ValueCreateDo(block);

out:
    DoDealloc(block);
    return NULL;
}
