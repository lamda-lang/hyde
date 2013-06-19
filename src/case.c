#include "case.h"

typedef struct {
    Element match;
    Element guard;
    Element value;
} Clause;

struct Case {
    Value base;
    Integer8 length;
    Clause clause[];
};

static Case *Create(Integer8 length, Error *error) {
    Case *block = MemoryAlloc(sizeof(Case) + sizeof(Clause) * length, error);
    if (block == NULL) {
	goto returnError;
    }
    block->base = TypeCase;
    block->length = length;
    return block;

returnError:
    return NULL;
}

Value *CaseDecode(Byte **bytes, Error *error) {
    Integer8 count = DecodeInteger8FLE(bytes);
    Case *block = Create(count, error);
    if (block == NULL) {
	goto returnError;
    }
    for (Integer8 index = 0; index < count; index += 1) {
	Clause *clause = &block->clause[index];
	clause->match.index = DecodeInteger32VLE(bytes);
	clause->guard.index = DecodeInteger32VLE(bytes);
	clause->value.index = DecodeInteger32VLE(bytes);
    }
    return BridgeFromCase(block);

returnError:
    return NULL;
}

void CaseFetch(Value *caseValue, Value **values) {
    Case *block = BridgeToCase(caseValue);
    for (Integer8 index = 0; index < block->length; index += 1) {
	Clause *clause = &block->clause[index];
	clause->match.value = values[clause->match.index];
	clause->guard.value = values[clause->guard.index];
	clause->value.value = values[clause->value.index];
    }
}

void CaseDealloc(Value *caseValue) {
    MemoryDealloc(caseValue);
}

Integer64 CaseHash(Value *caseValue) {
    return BridgeToCase(caseValue)->length;
}

void CaseEnumerate(Value *caseValue, void (*callback)(Value *value)) {
    Case *block = BridgeToCase(caseValue);
    for (Integer8 index = 0; index < block->length; index += 1) {
	callback(block->clause[index].match.value);
	callback(block->clause[index].guard.value);
	callback(block->clause[index].value.value);
    }
}

Value *CaseEval(Value *caseValue, bool pure, Error *error) {
    Case *block = BridgeToCase(caseValue);
    for (Integer8 index = 0; index < block->length; index += 1) {
	Clause *clause = &block->clause[index];
	Value *match = ValueEval(clause->match.value, true, error);
	if (match == NULL) {
	    goto returnError;
	}
	Value *guard = ValueEval(clause->guard.value, true, error);
	if (guard == NULL) {
	    goto returnError;
	}
	Value *value = ValueEval(clause->value.value, true, error);
	if (value == NULL) {
	    goto returnError;
	}
	clause->match.value = match;
        clause->guard.value = guard;
	clause->value.value = value;
    }
    return caseValue;

returnError:
    return NULL;
}
