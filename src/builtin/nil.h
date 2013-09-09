#ifndef BUILTIN_NIL_H
#define BUILTIN_NIL_H

#include <runtime.h>

Value *NilDecode(Byte **bytes, Error *error);
Bool NilEqual(void *nilModel, void *otherModel);

#endif
