#include "api.h"

struct Set {
    Value base;
    Integer32 length;
    Value *element[];
};

typedef struct {
    Integer32 count;
    Integer32 index[];
} Model;

static Integer32 IndexForValue(Set *set, Value *value, Integer32 offset) {
    return (ValueHash(value) + offset) % set->length;
}

static void AddValue(Set *set, Value *value) {
    Integer32 index = IndexForValue(set, value, 0);
    while (set->element[index] != NULL) {
	index = IndexForValue(set, value, index);
    }
   set->element[index] = value;
}

static Set *Create(Integer32 length, Error *error) {
    Set *set = MemoryAlloc(sizeof(Set) + sizeof(Value *) * length, error);
    if (set == NULL) {
        goto returnError;
    }
    set->base = TypeSet;
    set->length = length;
    for (Integer32 index = 0; index < length; index += 1) {
	set->element[index] = NULL;
    }
    return set;

returnError:
    return NULL;
}

void *SetDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32VLE(bytes);
    Model *model = MemoryAlloc(sizeof(Model) + sizeof(Integer32) * count, error);
    if (model == NULL) {
	goto returnError;
    }
    model->count = count;
    for (Integer32 index = 0; index < count; index += 1) {
	model->index[index] = DecodeInteger32VLE(bytes);
    }
    return model;

returnError:
    return NULL;
}

Value *SetEval(void *data, Code *code, bool pure, Error *error) {
    Model *model = data;
    Set *set = Create(model->count * 2, error);
    if (set == NULL) {
	goto returnError;
    }
    Value *setValue = BridgeFromSet(set);
    for (Integer32 index = 0; index < model->count; index += 1) {
	Value *value = CodeEvalInstructionAtIndex(code, model->index[index], true, error);
	if (value == NULL) {
	    goto deallocSet;
	}
	AddValue(set, value);
    }
    return setValue;

deallocSet:
    SetDealloc(setValue);
returnError:
    return NULL;
}

void SetDealloc(Value *setValue) {
    MemoryDealloc(setValue);
}

Integer64 SetHash(Value *setValue) {
    return BridgeToSet(setValue)->length;
}

void SetEnumerate(Value *setValue, void (*callback)(Value *value)) {
    Set *set = BridgeToSet(setValue);
    for (Integer32 index = 0; index < set->length; index += 1) {
	Value *value = set->element[index];
	if (value != NULL) {
	    callback(value);
	}
    }
}
