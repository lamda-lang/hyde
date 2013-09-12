#ifndef BUILTIN_COMPREHENSION_H
#define BUILTIN_COMPREHENSION_H

#include <runtime.h>

Value *ComprehensionDecodeList(Byte **bytes);
Value *ComprehensionDecodeMap(Byte **bytes);
Value *ComprehensionDecodeSet(Byte **bytes);
Bool ComprehensionEqual(Comprehension *comprehension, Comprehension *other);
void ComprehensionRelease(Comprehension *comprehension);

#endif
