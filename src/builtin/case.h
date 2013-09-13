#ifndef BUILTIN_CASE_H
#define BUILTIN_CASE_H

#include <runtime.h>

typedef struct Case Case;

Value *CaseDecode(Byte **bytes);
Bool CaseEqual(Case *block, Case *other);
Size CaseRelease(Case *block);

#endif
