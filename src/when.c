#include "when.h"

typedef struct {
    Element condition;
    Element value;
} Clause;

struct When {
    Value base;
    Integer8 count;
    Clause clause[];
};

static When *Create(Integer8 count, Error *error) {
    Size size = sizeof(When) * sizeof(Clause) * count;
    When *block = MemoryAlloc(size, error);
    if (block == NULL) {
	goto returnError;
    }
    block->base = TypeWhen;
    block->count = count;
    return block;

returnError:
    return NULL;
}

Value *WhenValueBridge(When *block) {
    return (Value *)block;
}

Value *WhenDecode(Byte **bytes, Error *error) {
    Integer8 count = DecodeInteger8FLE(bytes);
    When *block = Create(count, error);
    if (block == NULL) {
	goto returnError;
    }
    for (Integer8 index = 0; index < count; index += 1) {
	block->clause[index].condition.index = DecodeInteger32VLE(bytes);
	block->clause[index].value.index = DecodeInteger32VLE(bytes);
    }
    return WhenValueBridge(block);

returnError:
    return NULL;
}

void WhenFetch(Value *whenValue, Value **values) {
    When *block = ValueWhenBridge(whenValue, NULL);
    for (Integer8 index = 0; index < block->count; index += 1) {
	Integer32 conditionIndex = block->clause[index].condition.index;
	Integer32 valueIndex = block->clause[index].value.index;
	block->clause[index].condition.value = values[conditionIndex];
	block->clause[index].value.value = values[valueIndex];
    }
}

Value *WhenValue(When *block) {
}

void WhenDealloc(Value *whenValue) {
    MemoryDealloc(whenValue);
}

void WhenEnumerate(Value *whenValue, void (*callback)(Value *value)) {
    When *block = ValueWhenBridge(whenValue, NULL);
    for (Integer8 index = 0; index < block->count; index += 1) {
	Value *condition = block->clause[index].condition.value;
	Value *value = block->clause[index].value.value;
	callback(condition);
	callback(value);
    }
}
