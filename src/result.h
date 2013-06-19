#ifndef RESULT_H
#define RESULT_H

#include "api.h"

void ResultDealloc(Value *resultValue);

Value *ResultEval(Value *resultValue, bool pure, Error *error);

Value *ResultDecode(Byte **bytes, Error *error);

void ResultFetch(Value *resultValue, Value **values);

#endif
