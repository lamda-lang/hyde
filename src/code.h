#ifndef CODE_H
#define CODE_H

#include "api.h"

Code *CodeDecode(Byte **byte, Error *error);
Value *CodeEvalInstructionAtIndex(Code *code, Integer32 index, bool pure, Error *error);

#endif
