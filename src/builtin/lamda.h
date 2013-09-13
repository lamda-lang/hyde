#ifndef BUILTIN_LAMDA_H
#define BUILTIN_LAMDA_H

#include <runtime.h>

typedef struct Lamda Lamda;

Value *LamdaDecode(Byte **bytes);
Size LamdaRelease(Lamda *lamda);
Bool LamdaEqual(Lamda *lamda, Lamda *other);

#endif
