#ifndef BUILTIN_CASE_H
#define BUILTIN_CASE_H

#include <runtime.h>

Value *CaseDecode(Byte **bytes);
Bool CaseEqual(void *caseData, void *otherData);
void CaseRelease(void *caseData);

#endif
