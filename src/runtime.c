#include "runtime.h"

static void DeallocArgs(Value *listValue, Integer8 count) {
    List *list = ValueListBridge(listValue);
    for (Integer8 index = 0; index < count; index += 1) {
	Value *value = ListGetValueAtIndex(list, index);
	ValueDealloc(value);
    }
    ListDealloc(listValue);
}

static Value *CreateRoot(Char *root, Error *error) {
    Identifier *id = IdentifierCreateWithCharacters(root, error);
    if (id == NULL) {
	goto returnError;
    }
    return IdentifierValueBridge(id);

returnError:
    return NULL;
}

static Value *CreateArgs(Char **args, Integer8 count, Error *error) {
    List *list = ListCreate(count, error);
    Value *listValue = ListValueBridge(list);
    if (list == NULL) {
	goto returnError;
    }
    Integer8 stringCount = 0;
    for (Integer8 index = 0; index < count; index += 1) {
	String *string = StringCreateWithCharacters(args[index], error);
	if (string == NULL) {
	    goto deallocList;
	}
	Value *stringValue = StringValueBridge(string);
	ListSetValueAtIndex(list, stringValue, index);
	stringCount += 1;
    }
    return listValue;

deallocList:
    DeallocArgs(listValue, stringCount);
returnError:
    return NULL;
}

static Data *CreateData(Char *path, Error *error) {
    Data *data = DataCreate(error);
    if (data == NULL) {
	goto returnError;
    }
    File *file = FileOpen(path, error);
    if (file == NULL) {
	goto deallocData;
    }
    if (FileRead(file, data, error) == StatusFailure) {
	goto closeFile;
    }
    if (FileClose(file, error) == StatusFailure) {
	goto deallocData;
    }
    return data;

closeFile:
    FileClose(file, NULL);
deallocData:
    DataDealloc(data);
returnError:
    return NULL;
}

Status RuntimeMain(Char *path, Char **args, Integer8 count, Char *root, Error *error) {
    Data *data = CreateData(path, error);
    if (data == NULL) {
	goto returnError;
    }
    Value *listArgs = CreateArgs(args, count, error);
    if (listArgs == NULL) {
	goto deallocData;
    }
    Value *idRoot= CreateRoot(root, error);
    if (idRoot == NULL) {
	goto deallocArgs;
    }
    Byte *code = DataBytes(data);
    ExecuteCode(code, NULL, error);
    
    DeallocArgs(listArgs, count);
    DataDealloc(data);
    return StatusSuccess;

deallocArgs:
    DeallocArgs(listArgs, count);
deallocData:
    DataDealloc(data);
returnError:
    return StatusFailure;
}
