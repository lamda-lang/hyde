#ifndef BUILTIN_LIST_H
#define BUILTIN_LIST_H

#include <runtime.h>

typedef struct List List;

Value *ListDecode(Byte **bytes);
Bool ListEqual(List *list, List *other);
Size ListRelease(List *list);

#endif
