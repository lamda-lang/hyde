#ifndef WHEN_H
#define WHEN_H

#include "api.h"

void *WhenDecode(Byte **bytes, Error *error);
Value *WhenEval(void *data, Code *code, bool pure, Error *error);

#endif
