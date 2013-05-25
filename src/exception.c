#include <stdio.h>
#include <stdlib.h>
#include "exception.h"

typedef struct {
  Exception exception;
  bool pending;
} State;

static State state = {
  .pending = false
};

static Char *string[] = {
  [ExceptionOutOfMemory] = "OutOfMemory"
};

static void ExceptionAbort(Exception exception) {
  fprintf(stderr, "Exception: %s\n", string[exception]);
  abort();
}

void ExceptionRaise(Exception exception) {
  if (state.pending) {
    ExceptionAbort(exception);
  }
  state.exception = exception;
  state.pending = true;
}

Exception ExceptionCatch(void) {
  state.pending = false;
  return state.exception;
}
