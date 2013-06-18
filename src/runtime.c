#include "runtime.h"

static void DeallocArgs(Value *listValue, Integer8 count) {
    List *list = ValueListBridge(listValue);
    for (Integer8 index = 0; index < count; index += 1) {
	Value *value = ListGetValueAtIndex(list, index);
	ValueDealloc(value);
    }
    ListDealloc(listValue);
}

static Lamda *MainFromModule(Module *module, Char *rootName, Error *error) {
    Identifier *id = IdentifierCreateWithCharacters(rootName, error);
    Value *idValue = IdentifierValueBridge(id);
    if (id == NULL) {
	goto returnError;
    }
    Value *main = ModuleGetValueForIdentifier(module, id);
    if (main == NULL) {
	*error = ErrorMainNotFound;
	goto deallocID;
    }
    if (ValueType(main) != TypeLamda) {
	*error = ErrorInvalidType;
	goto deallocID;
    }
    IdentifierDealloc(idValue);
    return ValueLamdaBridge(main);

deallocID:
    IdentifierDealloc(idValue);
returnError:
    return NULL;
}

static Status EvalProgram(Lamda *main, Char **args, Integer8 count, Error *error) {
    List *list = ListCreate(count, error);
    Value *listValue = ListValueBridge(list);
    if (list == NULL) {
	goto returnError;
    }
    Integer8 stringCount = 0;
    for (Integer8 index = 0; index < count; index += 1) {
	String *string = StringCreateWithCharacters(args[index], error);
	if (string == NULL) {
	    goto deallocArgs;
	}
	Value *stringValue = StringValueBridge(string);
	ListSetValueAtIndex(list, stringValue, index);
	stringCount += 1;
    }
    Value *result = LamdaResult(main, &listValue, 1, error);
    if (result == NULL) {
	goto deallocArgs;
    }
    Value *eval = ValueEval(result, false, error);
    if (eval == NULL) {
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
    if (ModuleLoad(path, error) == StatusFailure) {
	goto returnError;
    }
    Module *module = ModuleWithID(path);
    Lamda *lamda = MainFromModule(module, main, error);
    if (lamda == NULL) {
	goto returnError;
    }
    return EvalProgram(lamda, args, count, error);

returnError:
    return StatusFailure;
}
