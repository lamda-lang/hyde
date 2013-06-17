#include <stdlib.h>
#include "process.h"

void ProcessExitSuccess(void) {
    exit(EXIT_SUCCESS);
}

void ProcessExitFailure(void) {
    exit(EXIT_FAILURE);
}
