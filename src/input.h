#ifndef INPUT_H
#define INPUT_H

#include "api.h"

void *InputDecode(Byte **bytes, Error *error);
Value *InputEval(void *data, Code *code, Value **context, Bool pure, Error *error);

#endif
