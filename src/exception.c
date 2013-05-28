#include "exception.h"

struct Exception {
    Error error;
};

static Char *description[] = {
    [ErrorOutOfMemory] = "OutOfMemory",
    [ErrorInvalidType] = "InvalidType",
    [ErrorArityMismatch] = "ArityMismatch",
    [ErrorFileOpen] = "FileOpen",
    [ErrorFileRead] = "FileRead",
    [ErrorFileWrite] = "FileWrite",
    [ErrorFileClose] = "FileClose"
};

static Exception outOfMemory = {
  .error = ErrorOutOfMemory
};

Exception *ExceptionCreate(void) {
    Exception *exception = MemoryAlloc(sizeof(Exception), NULL);
    if (exception == NULL) {
	goto returnError;
    }
    return exception;

returnError:
    return &outOfMemory;
}

Status ExceptionStatus(Exception *exception) {
  return exception == &outOfMemory ? StatusFailure : StatusSuccess;
}

Char *ExceptionDescription(Exception *exception) {
  return description[exception->error];
}

void ExceptionDealloc(Exception *exception) {
    MemoryDealloc(exception);
}

void ExceptionRaise(Exception *exception, Error error) {
    if (exception != NULL) {
        exception->error = error;
    }
}
