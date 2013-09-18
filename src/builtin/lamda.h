#ifndef BUILTIN_LAMDA_H
#define BUILTIN_LAMDA_H

#include <runtime.h>

typedef struct Lamda Lamda;

Lamda *LamdaDecode(Byte **bytes);
Value *LamdaEval(Lamda *lamda, Value *context);
Value *LamdaEqual(Lamda *lamda, Lamda *other);
Size LamdaRelease(Lamda *lamda);

#endif
