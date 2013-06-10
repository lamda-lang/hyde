#ifndef CASE_H
#define CASE_H

#include "api.h"

Value *CaseDecode(Byte **bytes, Error *error);

void CaseDealloc(Value *caseValue);

Integer64 CaseHash(Value *caseValue);

void CaseEnumerate(Value *caseValue, void (*callback)(Value *value));

Value *CaseEval(Value *caseValue, Error *error);

#endif
