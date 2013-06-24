#include "do.h"

typedef struct {
    Integer32 count;
    Integer32 element[];
} Model;

struct Do {
  Value base;
  Integer32 count;
  Value *element[];
};

static Do *Create(Integer32 count, Error *error) {
    Do *block = MemoryAlloc(sizeof(Do) * sizeof(Value *) * count, error);
    if (block == NULL) {
	goto returnError;
    }
    block->base = TypeDo;
    block->count = count;
    return block;

returnError:
    return NULL;
}

void *DoDecode(Byte **bytes, Error *error) {
    Integer32 count = DecodeInteger32VLE(bytes);
    Model *model = MemoryAlloc(sizeof(Model) + sizeof(Integer32) * count, error);
    if (model == NULL) {
	goto returnError;
    }
    model->count = count;
    for (Integer32 index = 0; index < count; index += 1) {
	model->element[index] = DecodeInteger32VLE(bytes);
    }
    return model;

returnError:
    return NULL;
}

Value *DoEval(void *data, Code *code, bool pure, Error *error) {
    Model *model = data;
    Do *block = Create(model->count, error);
    if (block == NULL) {
	goto returnError;
    }
    Value *doValue = BridgeFromDo(block);
    for (Integer32 index = 0; index < model->count; index += 1) {
	Value *value = CodeEvalInstructionAtIndex(code, model->element[index], pure, error);
	if (value == NULL) {
	    goto deallocBlock;
	}
	block->element[index] = value;
    }
    return pure ? doValue : block->element[block->count - 1];

deallocBlock:
    DoDealloc(doValue);
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
        callback(block->element[index]);
    }
}
