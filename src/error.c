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

void ErrorPrint(Error error) {
    fprintf(stderr, "%s\n", string[error]);
}
