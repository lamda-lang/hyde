#ifndef VARIABLE_H
#define VARIABLE_H

#include "api.h"

void *VariableDecode(Byte **bytes, Error *error);
Value *VariableEval(void *data, Code *code, Value **context, Bool pure, Error *error);

#endif
