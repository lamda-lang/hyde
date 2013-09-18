#ifndef BUILTIN_LIST_H
#define BUILTIN_LIST_H

#include <runtime.h>

typedef struct List List;

List *ListDecode(Byte **bytes);
Value *ListEval(List *list, Value *context);
Value *ListEqual(List *list, List *other);
Size ListRelease(List *list);

#endif
