#include "do.h"

struct Do {
  Value base;
  Integer32 count;
  Element element[];
};

static Do *Create(Integer32 count, Error *error) {
    Do *block = MemoryAlloc(sizeof(Do) * sizeof(Element) * count, error);
    if (block == NULL) {
	goto returnError;
    }
    block->base = TypeDo;
    block->count = count;
    return block;

returnError:
    return NULL;
}

void DoDealloc(Value *doValue) {
    MemoryDealloc(doValue);
}

Integer64 DoHash(Value *doValue) {
    return BridgeToDo(doValue)->count;
}

void DoEnumerate(Value *doValue, void (*callback)(Value *value)) {
    Do *block = BridgeToDo(doValue);
    for (Integer32 index = 0; index < block->count; index += 1) {
	Value *value = block->element[index].value;
        callback(value);
    }
}
