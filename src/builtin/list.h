#ifndef BUILTIN_LIST_H
#define BUILTIN_LIST_H

#include <runtime.h>

Value *ListDecode(Byte **bytes);
Bool ListEqual(void *listData, void *otherData);
void ListRelease(void *listData);

#endif
