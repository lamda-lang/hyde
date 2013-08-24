#ifndef VARIABLE_H
#define VARIABLE_H

#include "runtime.h"

VALUE *VariableDecode(Byte **bytes, VALUE **error);
void VariableDealloc(VALUE *tokenValue);
Integer64 VariableHash(VALUE *tokenValue);
Bool VariableEqual(VALUE *tokenValue, VALUE *otherValue);

#endif
