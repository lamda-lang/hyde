#ifndef BUILTIN_CASE_H
#define BUILTIN_CASE_H

#include <runtime.h>

typedef struct Case Case;

Case *CaseDecode(Byte **bytes);
Value *CaseEval(Case *block, Value *context);
Value *CaseEqual(Case *block, Case *other);
Size CaseRelease(Case *block);

#endif
