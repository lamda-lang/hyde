#ifndef CASE_H
#define CASE_H

#include "runtime.h"

Size CaseSize(Case *block);
Case *CaseDecode(Byte **bytes, Error *error);
Value *CaseEval(Case *block, Value *context, Error *error);
Bool CaseEqual(Case *block, Case *other);
Size CaseRelease(Case *block);

#endif
