#ifndef CASE_H
#define CASE_H

#include "api.h"

void *CaseDecode(Byte **bytes, Error *error);
Value *CaseEval(void *data, Code *code, Value **context, Bool pure, Error *error);

#endif
