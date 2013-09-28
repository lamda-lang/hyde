#ifndef LAMDA_H
#define LAMDA_H

#include "runtime.h"

Size LamdaSize(Lamda *lamda);
Size LamdaEncode(Lamda *lamda, Byte **bytes);
Lamda *LamdaDecode(Byte **bytes, Error *error);
Value *LamdaEval(Value *value, Lamda *lamda, Value *context, Error *error);
Bool LamdaEqual(Lamda *lamda, Lamda *other);
Size LamdaRelease(Lamda *lamda);
Value *LamdaCall(Lamda *lamda, Value **args, Integer8 count, Error *error);

#endif
