#ifndef VARIABLE_H
#define VARIABLE_H

#include "runtime.h"

VALUE *VariableDecode(Byte **bytes, Error *error);
void VariableDealloc(VALUE *tokenValue);

#endif
