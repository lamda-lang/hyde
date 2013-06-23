#include "runtime.h"

static void DeallocArgs(Value *listValue, Integer8 count) {
    for (Integer8 index = 0; index < count; index += 1) {
	Value *value = ListGetValueAtIndex(listValue, index);
	ValueDealloc(value);
    }
    ListDealloc(listValue);
}

static Value *MainFromModule(Value *moduleValue, Char *rootName, Error *error) {
    Value *idValue = IdentifierCreateWithCharacters(rootName, error);
    if (idValue == NULL) {
	goto returnError;
    }
    Value *main = ModuleGetValueForIdentifier(moduleValue, idValue);
    if (main == NULL) {
	*error = ErrorMainNotFound;
	goto deallocID;
    }
    if (ValueType(main) != TypeLamda) {
	*error = ErrorInvalidType;
	goto deallocID;
    }
    IdentifierDealloc(idValue);
    return main;

deallocID:
    IdentifierDealloc(idValue);
returnError:
    return NULL;
}

static Status EvalProgram(Value *lamdaValue, Char **args, Integer8 count, Error *error) {
    Value *listValue = ListCreate(count, error);
    if (listValue == NULL) {
	goto returnError;
    }
    Integer8 stringCount = 0;
    for (Integer8 index = 0; index < count; index += 1) {
	Value *stringValue = StringCreateWithCharacters(args[index], error);
	if (stringValue == NULL) {
	    goto deallocArgs;
	}
	ListSetValueAtIndex(listValue, stringValue, index);
	stringCount += 1;
    }
    Value *result = LamdaResult(lamdaValue, &listValue, 1, error);
    if (result == NULL) {
	goto deallocArgs;
    }
    DeallocArgs(listValue, stringCount);
    return StatusSuccess;

deallocArgs:
    DeallocArgs(listValue, stringCount);
returnError:
    return StatusFailure;
}

Status RuntimeMain(Char *path, Char *main, Char **args, Integer8 count, Error *error) {
    Value *moduleValue = NULL; /* missing */
    if (moduleValue == NULL) {
	goto returnError;
    }
    Value *lamdaValue = MainFromModule(moduleValue, main, error);
    if (lamdaValue == NULL) {
	goto returnError;
    }
    return EvalProgram(lamdaValue, args, count, error);

returnError:
    return StatusFailure;
}
