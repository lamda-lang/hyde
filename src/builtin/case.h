#ifndef CASE_H
#define CASE_H

#include <runtime.h>

VALUE *CaseDecode(Byte **bytes, Error *error);
VALUE *CaseEval(VALUE *caseValue, Bool pure, Error *error);

#endif
