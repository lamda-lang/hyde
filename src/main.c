#include <stdio.h>
#include <stdlib.h>
#include "api.h"

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

static Value *ExecuteBytecode(Data *data, Error *error) {
    Byte *code = DataBytes(data);
    Integer32 registerCount = DecodeInteger32VLE(&code);
    Integer32 instructionCount = DecodeInteger32VLE(&code);
    Stack *stack = StackCreate(256, error);
    if (stack == NULL) {
	goto returnError;
    }
    if (StackBuildNextFrame(stack, registerCount, error) == StatusFailure) {
	goto deallocStack;
    }
    if (ExecuteCode(code, instructionCount, stack, error) == StatusFailure) {
	goto deallocStack;
    }
    Value *result = *StackResultFromTopFrame(stack);
    StackDealloc(stack);
    return result;

deallocStack:
    StackDealloc(stack);
returnError:
    return NULL;
}

static void PrintValue(Value *value) {
    String *string = ValueStringBridge(value);
    Integer32 length = StringLength(string);
    Integer32 *codepoints = StringCodepoints(string);
    for (Integer32 index = 0; index < length; index += 1) {
	Integer32 codepoint = codepoints[index];
	if (codepoint >= 32 && codepoint <= 126) {
	    putchar(codepoint & 0XFF);
	}
    }
    putchar('\n');
}

int main(int argc, char **argv) {
    Error error = 0;
    Data *data = DataFromPath(argv[1], &error);
    if (data == NULL) {
	goto returnError;
    }
    Value *result = ExecuteBytecode(data, &error);
    if (result == NULL) {
	goto deallocData;
    }
    PrintValue(result);
    DataDealloc(data);
    return EXIT_SUCCESS;

deallocData:
    DataDealloc(data);
returnError:
    return EXIT_FAILURE;
}
