#ifndef SET_H
#define SET_H

#include "runtime.h"

Set *SetDecode(Byte **bytes);
Set *SetEval(Set *set, Value *context);
Bool SetEqual(Set *set, Set *other);
Size SetRelease(Set *set);

#endif
