#include "case.h"

struct Case {
    Value base;
};

Value *CaseDecode(Byte **bytes, Error *error) {
    return NULL;
}

void CaseDealloc(Value *caseValue) {
}

Integer64 CaseHash(Value *caseValue) {
    return 0;
}

void CaseEnumerate(Value *caseValue, void (*callback)(Value *value)) {
}

Value *CaseEval(Value *caseValue, Error *error) {
    return NULL;
}
