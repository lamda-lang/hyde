#include "exception.h"

struct Exception {
    Error error;
};

Exception *ExceptionCreate(void) {
    return MemoryAlloc(sizeof(Exception), NULL);
}

void ExceptionRaise(Exception *exception, Error error) {
    if (exception != NULL) {
        exception->error = error;
    }
}
