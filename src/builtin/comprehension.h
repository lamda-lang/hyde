#ifndef BUILTIN_COMPREHENSION_H
#define BUILTIN_COMPREHENSION_H

#include <runtime.h>

Value *ComprehensionDecodeList(Byte **bytes);
Value *ComprehensionDecodeMap(Byte **bytes);
Value *ComprehensionDecodeSet(Byte **bytes);
Bool ComprehensionEqual(void *comprehensionData, void *otherData);
void ComprehensionRelease(void *comprehensionData);

#endif
