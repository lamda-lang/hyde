#include "RTError.h"

const char *message[] = {
  [RTErrorOutOfMemory] = "RTErrorOutOfMemory",
  [RTErrorInvalidType] = "RTErrorInvalidType",
  [RTErrorInvalidOpcode] = "RTErrorInvalidOpcode",
  [RTErrorArityMismatch] = "RTErrorArityMismatch",
  [RTErrorReadFile] = "RTErrorReadFile",
  [RTErrorWriteFile] = "RTErrorWriteFile",
  [RTErrorInvalidEncoding] = "RTErrorInvalidEncoding"
};

void RTErrorShow(RTError error) {
  fprintf(stderr, "runtime error: %s\n", message[error]);
}
