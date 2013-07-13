#ifndef RESULT_H
#define RESULT_H

#include "api.h"

void *ResultDecode(Byte **bytes, Error *error);
Value *ResultEval(void *data, Code *code, Value **context, Bool pure, Error *error);

#endif
