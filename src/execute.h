#ifndef EXECUTE_H
#define EXECUTE_H

#include "api.h"

Value *ExecuteCode(Byte *bytes, void (*callback)(Value **values), Error *error);

#endif
