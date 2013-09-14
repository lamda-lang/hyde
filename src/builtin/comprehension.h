#ifndef BUILTIN_COMPREHENSION_H
#define BUILTIN_COMPREHENSION_H

#include <runtime.h>

typedef struct Comprehension Comprehension;

Value *ComprehensionDecode(Byte **bytes);
Value *ComprehensionEval(Comprehension *comprehension, Value *context);
Bool ComprehensionEqual(Comprehension *comprehension, Comprehension *other);
Size ComprehensionRelease(Comprehension *comprehension);

#endif
