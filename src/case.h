#ifndef CASE_H
#define CASE_H

#include "runtime.h"

Case *CaseDecode(Byte **bytes);
Value *CaseEval(Case *block, Value *context);
Bool CaseEqual(Case *block, Case *other);
Size CaseRelease(Case *block);

#endif
