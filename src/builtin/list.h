#ifndef BUILTIN_LIST_H
#define BUILTIN_LIST_H

#include <runtime.h>

Value *ListDecode(Byte **bytes);
Bool ListEqual(List *list, List *other);
void ListRelease(List *list);

#endif
