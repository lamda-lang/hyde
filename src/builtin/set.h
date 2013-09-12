#ifndef BUILTIN_SET_H
#define BUILTIN_SET_H

#include <runtime.h>

Value *SetDecode(Byte **bytes);
void SetRelease(Set *set);
Bool SetEqual(Set *set, Set *other);

#endif
