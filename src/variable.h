#ifndef VARIABLE_H
#define VARIABLE_H

#include "runtime.h"

VALUE *VariableDecode(Byte **bytes, VALUE **error);
void VariableDealloc(VALUE *tokenValue);

#endif
