#ifndef EXECUTE_H
#define EXECUTE_H

#include "api.h"

Status ExecuteCode(Byte *bytes, Value **values, Integer32 valueCount, Error *error);

#endif
