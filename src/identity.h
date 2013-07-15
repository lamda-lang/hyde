#ifndef IDENTITY_H
#define IDENTITY_H

#include "api.h"

void *IdentityDecode(Byte **bytes, Error *error);
Value *IdentityEval(void *data, Code *code, Value **context, Bool pure, Error *error);

#endif
