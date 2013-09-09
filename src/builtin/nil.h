#ifndef NIL_H
#define NIL_H

#include <runtime.h>

Value *NilConstant(void);
Value *NilDecode(Byte **bytes, Error *error);
Bool NilEqual(Value *nilValue, Value *otherValue);

#endif
