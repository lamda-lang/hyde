#ifndef BUILTIN_LIST_H
#define BUILTIN_LIST_H

#include <runtime.h>

Value *ListDecode(Byte **bytes, Error *error);
Bool ListEqual(void *listModel, void *otherModel);
void ListRelease(void *listModel);

#endif
