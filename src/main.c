#include <stdio.h>
#include <stdlib.h>
#include "api.h"
/*
static Data *DataFromPath(Char *path, Error *error) {
    File *file = FileOpen(path, error);
    if (file == NULL) {
	goto returnError;
    }
    Data *code = FileRead(file, error);
    if (code == NULL) {
	goto closeFile;
    }
    FileClose(file, NULL);
    return code;

closeFile:
    FileClose(file, NULL);
returnError:
    return NULL;
}

static Map *ExecuteBytecode(Data *data, Error *error) {
    Byte *code = DataBytes(data);
    Integer32 valueCount = DecodeInteger32VLE(&code);
    Stack *stack = StackCreate(256, error);
    if (stack == NULL) {
	goto returnError;
    }
    if (StackPushFrame(stack, valueCount, error) == StatusFailure) {
	goto deallocStack;
    }
    if (ExecuteCode(code, valueCount, stack, error) == StatusFailure) {
	goto deallocStack;
    }
    Value *result = *StackFrameResult(stack);
    StackDealloc(stack);
    return ValueMapBridge(result);

deallocStack:
    StackDealloc(stack);
returnError:
    return NULL;
}

static Value *MainFromMap(Map *map, Integer8 argCount, Value **args, Error *error) {
    return NULL;
}

static void ExecuteTree(Value *root) {
}

int main(int argc, char **argv) {
    Error error;
    Data *data = DataFromPath(argv[1], &error);
    if (data == NULL) {
	goto returnError;
    }
    Map *map = ExecuteBytecode(data, &error);
    if (map == NULL) {
	goto deallocData;
    }
    Integer8 argCount = argc;
    Value *arg[argCount];
    Value *main = MainFromMap(map, argCount, arg, error);
    if (main == NULL) {
	goto deallocData;
    }
    ExecuteTree(main);
    DataDealloc(data);
    return EXIT_SUCCESS;

deallocData:
    DataDealloc(data);
returnError:
    return EXIT_FAILURE;
}
*/
