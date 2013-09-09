#ifndef CASE_H
#define CASE_H

#include <runtime.h>

Value *CaseDecode(Byte **bytes, Error *error);
Bool CaseEqual(Value *caseValue, Value *otherValue);
void CaseRelease(Value *caseValue);

#endif
