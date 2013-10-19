#ifndef CASE_H
#define CASE_H

#include "runtime.h"

Bool CaseDecode(Binary *binary, Integer32 *offset, Value **value);
Bool CaseEval(Case *block, Context *context, Stack *stack);

#endif
