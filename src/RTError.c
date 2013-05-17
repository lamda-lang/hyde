#include "RTError.h"

const char *message[] = {
  [RTErrorOutOfMemory] = "RTErrorOutOfMemory",
  [RTErrorInvalidType] = "RTErrorInvalidType",
  [RTErrorInvalidOpcode] = "RTErrorInvalidOpcode",
  [RTErrorArityMismatch] = "RTErrorArityMismatch",
  [RTErrorReadFile] = "RTErrorReadFile",
  [RTErrorWriteFile] = "RTErrorWriteFile"
};

void RTErrorShow(RTError error) {
  perror(message[error]);
}
