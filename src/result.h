#ifndef RESULT_H
#define RESULT_H

#include "api.h"

void *ResultDecode(Byte **bytes, Error *error);
Value *ResultEval(void *data, Code *code, bool pure, Error *error);

#endif
