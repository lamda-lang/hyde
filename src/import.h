#ifndef IMPORT_H
#define IMPORT_H

#include "api.h"

void *ImportDecode(Byte **bytes, Error *error);
Value *ImportEval(void *data, Code *code, Value **context, bool pure, Error *error);

#endif
