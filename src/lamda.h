#ifndef LAMDA_H
#define LAMDA_H

#include "runtime.h"

Size LamdaSize(Lamda *lamda);
Size LamdaEncode(Lamda *lamda, Byte **bytes);
Lamda *LamdaDecode(Byte **bytes, Error *error);
Lamda *LamdaEval(Lamda *lamda, Value *context, Error *error);
Bool LamdaEqual(Lamda *lamda, Lamda *other);
Size LamdaRelease(Lamda *lamda);

#endif
