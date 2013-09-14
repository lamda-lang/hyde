#ifndef BUILTIN_SET_H
#define BUILTIN_SET_H

#include <runtime.h>

typedef struct Set Set;

Value *SetDecode(Byte **bytes);
Value *SetEval(Set *set, Value *context);
Size SetRelease(Set *set);
Bool SetEqual(Set *set, Set *other);

#endif
