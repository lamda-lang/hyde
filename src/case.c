#include "case.h"

typedef struct {
    Integer32 match;
    Integer32 guard;
    Integer32 value;
} Clause;

typedef struct {
    Integer8 length;
    Integer32 arg;
    Clause clause[];
} Model;

void *CaseDecode(Byte **bytes, Error *error) {
    Integer8 length = DecodeInteger8FLE(bytes);
    Model *model = MemoryAlloc(sizeof(Model) + sizeof(Clause) * length, error);
    if (model == NULL) {
	goto returnError;
    }
    model->length = length;
    model->arg = DecodeInteger32VLE(bytes);
    for (Integer8 index = 0; index < length; index += 1) {
	model->clause[index].match = DecodeInteger32VLE(bytes);
	model->clause[index].guard = DecodeInteger32VLE(bytes);
	model->clause[index].value = DecodeInteger32VLE(bytes);
    }
    return model;

returnError:
    return NULL;
}

Value *CaseEval(void *data, Code *code, bool pure, Error *error) {
    Model *model = data;
    Value *arg = CodeEvalInstructionAtIndex(code, model->arg, true, error);
    if (arg == NULL) {
	goto returnError;
    }
    for (Integer8 index = 0; index < model->length; index += 1) {
	Clause clause = model->clause[index];
	Value *match = CodeEvalInstructionAtIndex(code, clause.match, true, error);
	if (match == NULL) {
	    goto returnError;
	}
	if (ValueEqual(arg, match)) {
	    Value *guard = CodeEvalInstructionAtIndex(code, clause.guard, true, error);
	    if (guard == NULL) {
		goto returnError;
	    }
	    if (guard == GlobalBooleanTrue) {
		return CodeEvalInstructionAtIndex(code, clause.value, pure, error);
	    }
	}
    }
    return GlobalNil;

returnError:
    return NULL;
}
