#ifndef SET_H
#define SET_H

#include "runtime.h"

Size SetSize(Set *set);
Size SetEncode(Set *set, Byte **bytes);
Set *SetDecode(Byte **bytes, Error *error);
Value *SetEval(Value *value, Set *set, Value *context, Error *error);
Bool SetEqual(Set *set, Set *other);
Size SetRelease(Set *set);

#endif
