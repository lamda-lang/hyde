#ifndef LIST_H
#define LIST_H

#include "runtime.h"

Size ListSize(List *list);
List *ListDecode(Byte **bytes, Error *error);
List *ListEval(List *list, Value *context, Error *error);
Bool ListEqual(List *list, List *other);
Size ListRelease(List *list);

#endif
