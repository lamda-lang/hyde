#ifndef RUNTIME_H
#define RUNTIME_H

#include "api.h"

Runtime *RuntimeCreate(Error *error);
VALUE *RuntimeLoad(Char *path, Error *error);
VALUE *RuntimeEval(VALUE *value, Error *error);

#endif
