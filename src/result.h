#ifndef RESULT_H
#define RESULT_H

#include "api.h"

Value *ResultValueBridge(Result *result);

Value *ResultDecode(Byte **bytes, Error *error);

void ResultFetch(Value *resultValue, Value **values);

#endif
