#ifndef CODE_H
#define CODE_H

#include "api.h"

Code *CodeDecode(Byte **byte, Error *error);
Value *CodeEvalInstructionAtIndex(Code *code, Value **context, Integer32 index, Bool pure, Error *error);

#endif
