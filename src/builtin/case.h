#ifndef BUILTIN_CASE_H
#define BUILTIN_CASE_H

#include <builtin/api.h>
#include <posix/api.h>
#include <util/api.h>

VALUE *CaseDecode(Byte **bytes, Error *error);
VALUE *CaseEval(VALUE *caseValue, Bool pure, Error *error);

#endif
