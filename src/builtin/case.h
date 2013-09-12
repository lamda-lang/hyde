#ifndef BUILTIN_CASE_H
#define BUILTIN_CASE_H

#include <runtime.h>

Value *CaseDecode(Byte **bytes);
Bool CaseEqual(Case *block, Case *other);
void CaseRelease(Case *block);

#endif
