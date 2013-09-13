#ifndef BUILTIN_COMPREHENSION_H
#define BUILTIN_COMPREHENSION_H

#include <runtime.h>

typedef struct Comprehension Comprehension;

Value *ComprehensionDecodeList(Byte **bytes);
Value *ComprehensionDecodeMap(Byte **bytes);
Value *ComprehensionDecodeSet(Byte **bytes);
Bool ComprehensionEqual(Comprehension *comprehension, Comprehension *other);
Size ComprehensionRelease(Comprehension *comprehension);

#endif
