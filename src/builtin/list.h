#ifndef BUILTIN_LIST_H
#define BUILTIN_LIST_H

#include <runtime.h>

typedef struct List List;

List *ListDecode(Byte **bytes);
List *ListEval(List *list, Value *context);
Bool ListEqual(List *list, List *other);
Size ListRelease(List *list);

#endif
