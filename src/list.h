#ifndef LIST_H
#define LIST_H

#include "runtime.h"

List *ListDecode(Byte **bytes);
List *ListEval(List *list, Value *context);
Bool ListEqual(List *list, List *other);
Size ListRelease(List *list);

#endif
