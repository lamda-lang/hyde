#ifndef BUILTIN_SET_H
#define BUILTIN_SET_H

#include <runtime.h>

typedef struct Set Set;

Set *SetDecode(Byte **bytes);
Value *SetEval(Set *set, Value *context);
Value *SetEqual(Set *set, Set *other);
Size SetRelease(Set *set);

#endif
