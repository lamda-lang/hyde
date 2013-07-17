#ifndef TAG_H
#define TAG_H

#include "api.h"

void *TagDecode(Byte **bytes, Error *error);
Value *TagEval(void *data, Code *code, Value **context, Bool pure, Error *error);
Value *TagCreateWithCharacters(Char *chars, Error *error);
void TagDealloc(Value *tagValue);
Integer64 TagHash(Value *tagValue);
Bool TagEqual(Value *tagValue, Value *otherValue);

#endif
