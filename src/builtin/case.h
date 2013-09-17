#ifndef BUILTIN_CASE_H
#define BUILTIN_CASE_H

#include <runtime.h>

typedef struct Case Case;

Value *CaseDecode(Byte **bytes);
Value *CaseEval(Case *block, Value *context);
Value *CaseEqual(Case *block, Case *other);
Size CaseRelease(Case *block);

#endif
