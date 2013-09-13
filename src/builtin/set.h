#ifndef BUILTIN_SET_H
#define BUILTIN_SET_H

#include <runtime.h>

typedef struct Set Set;

Value *SetDecode(Byte **bytes);
Size SetRelease(Set *set);
Bool SetEqual(Set *set, Set *other);

#endif
