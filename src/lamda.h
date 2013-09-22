#ifndef LAMDA_H
#define LAMDA_H

#include "runtime.h"

Lamda *LamdaDecode(Byte **bytes, Error *error);
Lamda *LamdaEval(Lamda *lamda, Value *context, Error *error);
Bool LamdaEqual(Lamda *lamda, Lamda *other);
Size LamdaRelease(Lamda *lamda);

#endif
