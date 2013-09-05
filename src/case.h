#ifndef CASE_H
#define CASE_H

#include "api.h"

VALUE *CaseDecode(Byte **bytes, Error *error);
VALUE *CaseEval(VALUE *caseValue, Bool pure, Error *error);

#endif
