#include <stdio.h>
#include "error.h"

static Char *string[] = {
    [ErrorOutOfMemory] = "ErrorOutOfMemory",
    [ErrorInvalidType] = "ErrorInvalidType",
    [ErrorArityMismatch] = "ErrorArityMismatch",
    [ErrorFileOpen] = "ErrorFileOpen",
    [ErrorFileRead] = "ErrorFileRead",
    [ErrorFileWrite] = "ErrorFileWrite",
    [ErrorFileClose] = "ErrorFileClose",
    [ErrorMainNotFound] = "ErrorMainNotFound"
};

void ErrorSet(Error *error, Error errno) {
    if (error != NULL) {
	*error = errno;
    }
}

void ErrorPrint(Error error) {
    fprintf(stderr, "%s\n", string[error]);
}
