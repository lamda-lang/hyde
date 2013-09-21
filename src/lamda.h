#ifndef LAMDA_H
#define LAMDA_H

#include "runtime.h"

Lamda *LamdaDecode(Byte **bytes);
Lamda *LamdaEval(Lamda *lamda, Value *context);
Bool LamdaEqual(Lamda *lamda, Lamda *other);
Size LamdaRelease(Lamda *lamda);

#endif
