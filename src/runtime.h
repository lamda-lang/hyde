#ifndef RUNTIME_H
#define RUNTIME_H

#include "api.h"

VALUE *RuntimeLoad(Byte *bytes, Error *error);
VALUE *RuntimeEval(VALUE *value, Error *error);

#endif
