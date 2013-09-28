#ifndef LIST_H
#define LIST_H

#include "runtime.h"

Size ListSize(List *list);
Size ListEncode(List *list, Byte **bytes);
List *ListDecode(Byte **bytes, Error *error);
Value *ListEval(Value *value, List *list, Value *context, Error *error);
Bool ListEqual(List *list, List *other);
Size ListRelease(List *list);

#endif
