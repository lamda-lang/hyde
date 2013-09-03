#ifndef RUNTIME_H
#define RUNTIME_H

#include "api.h"

Error RuntimeInitialize(void);
void RuntimeShutdown(void);
VALUE *RuntimeValueForConstant(Constant constant);
VALUE *RuntimeLoad(Byte *bytes, Error *error);
VALUE *RuntimeEval(VALUE *value, Error *error);

#endif
