#include <stdio.h>
#include <stdlib.h>
#include "api.h"

static inline Data *DataFromPath(Char *path, Exception *exception) {
    File *file = FileOpen(path, exception);
    if (file == NULL) {
	goto returnError;
    }
    Data *code = FileRead(file, exception);
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

static inline Value *ExecuteBytecode(Data *data, Exception *exception) {
    Byte *code = DataBytes(data);
    Integer32 registerCount = DecodeInteger32VLE(&code);
    Integer32 instructionCount = DecodeInteger32VLE(&code);
    Stack *stack = StackCreate(256, exception);
    if (stack == NULL) {
	goto returnError;
    }
    if (StackBuildNextFrame(stack, registerCount, exception) == StatusFailure) {
	goto deallocStack;
    }
    if (ExecuteCode(code, instructionCount, stack, exception) == StatusFailure) {
	goto deallocStack;
    }
    Value *result = StackReturnFromTopFrame(stack);
    StackDealloc(stack);
    return result;

deallocStack:
    StackDealloc(stack);
returnError:
    return NULL;
}

static inline void PrintValue(Value *value) {
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

static inline void PrintException(Exception *exception) {
  fprintf(stderr, "Exception: %s\n", ExceptionDescription(exception));
}

int main(int argc, char **argv) {
    Exception *exception = ExceptionCreate();
    if (ExceptionStatus(exception) == StatusFailure) {
	goto raiseException;
    }
    Data *data = DataFromPath(argv[1], exception);
    if (data == NULL) {
	goto raiseException;
    }
    Value *result = ExecuteBytecode(data, exception);
    if (result == NULL) {
	goto deallocData;
    }
    PrintValue(result);
    DataDealloc(data);
    ExceptionDealloc(exception);
    return EXIT_SUCCESS;

deallocData:
    DataDealloc(data);
raiseException:
    PrintException(exception);
    return EXIT_FAILURE;
}
