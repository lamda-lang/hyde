#include "do.h"

struct Do {
  Value base;
  Integer32 count;
  Element element[];
};

Value *DoValueBridge(Do *block) {
    return (Value *)block;
}

static Do *Create(Integer32 count, Error *error) {
    Size size = sizeof(Do) * sizeof(Element) * count;
    Do *block = MemoryAlloc(size, error);
    if (block == NULL) {
	goto returnError;
    }
    block->base = TypeDo;
    block->count = count;
    return block;

returnError:
    return NULL;
}

Value *DoDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32VLE(bytes);
    Do *block = Create(count, error);
    if (block == NULL) {
	goto returnError;
    }
    for (Integer32 index = 0; index < count; index += 1) {
	block->element[index].index = DecodeInteger32VLE(bytes);
    }
    return DoValueBridge(block);

returnError:
    return NULL;
}

void DoFetch(Value *doValue, Value **values) {
    Do *block = ValueDoBridge(doValue);
    for (Integer32 index = 0; index < block->count; index += 1) {
        Integer32 elementIndex = block->element[index].index;
	block->element[index].value = values[elementIndex];
    }
}

void DoDealloc(Value *doValue) {
    MemoryDealloc(doValue);
}

Integer64 DoHash(Value *doValue) {
    return ValueDoBridge(doValue)->count;
}

void DoEnumerate(Value *doValue, void (*callback)(Value *value)) {
    Do *block = ValueDoBridge(doValue);
    for (Integer32 index = 0; index < block->count; index += 1) {
	Value *value = block->element[index].value;
        callback(value);
    }
}

Value *DoEval(Value *doValue, Error *error) {
    Do *block = ValueDoBridge(doValue);
    for (Integer32 index = 0; index < block->count; index += 1) {
	Value *value = ValueEval(block->element[index].value, error);
	if (value == NULL) {
	    goto returnError;
	}
	block->element[index].value = value;;
    }
    Integer32 last =block->count - 1;
    return block->element[last].value;

returnError:
    return NULL;
}
