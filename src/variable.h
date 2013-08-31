#ifndef VARIABLE_H
#define VARIABLE_H

#include "api.h"

VALUE *VariableDecode(Byte **bytes, Error *error);
void VariableDealloc(VALUE *tokenValue);

#endif
