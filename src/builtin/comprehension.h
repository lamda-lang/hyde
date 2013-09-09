#ifndef COMPREHENSION_H
#define COMPREHENSION_H

#include <runtime.h>

Value *ComprehensionDecodeList(Byte **bytes, Error *error);
Value *ComprehensionDecodeMap(Byte **bytes, Error *error);
Value *ComprehensionDecodeSet(Byte **bytes, Error *error);
Bool ComprehensionEqual(Value *comprehensionValue, Value *otherValue);
void ComprehensionDealloc(Value *comprehensionValue);

#endif
