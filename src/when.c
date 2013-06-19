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
    When *block = MemoryAlloc(sizeof(When) * sizeof(Clause) * count, error);
    if (block == NULL) {
	goto returnError;
    }
    block->base = TypeWhen;
    block->count = count;
    return block;

returnError:
    return NULL;
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
    return BridgeFromWhen(block);

returnError:
    return NULL;
}

void WhenFetch(Value *whenValue, Value **values) {
    When *block = BridgeToWhen(whenValue);
    for (Integer8 index = 0; index < block->count; index += 1) {
	Integer32 conditionIndex = block->clause[index].condition.index;
	Integer32 valueIndex = block->clause[index].value.index;
	block->clause[index].condition.value = values[conditionIndex];
	block->clause[index].value.value = values[valueIndex];
    }
}

void WhenDealloc(Value *whenValue) {
    MemoryDealloc(whenValue);
}

Value *WhenEval(Value *whenValue, bool pure, Error *error) {
    When *block = BridgeToWhen(whenValue);
    for (Integer8 index = 0; index < block->count; index += 1) {
	Value *condition = ValueEval(block->clause[index].condition.value, true, error);
	if (condition == NULL) {
	    goto returnError;
	}
	if (condition == BooleanTrueSingleton()) {
	    return ValueEval(block->clause[index].value.value, pure, error);
	}
    }
    return NilSingleton();

returnError:
    return NULL;
}
