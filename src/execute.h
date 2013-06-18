#ifndef EXECUTE_H
#define EXECUTE_H

#include "api.h"

Value *ExecuteCode(Byte *bytes, Value **args, Integer8 argCount, Value **context, Integer8 contextLength, Error *error);

#endif
