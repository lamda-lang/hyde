#ifndef NIL_H
#define NIL_H

#include "runtime.h"

Size NilSize(Nil *nil);
Size NilEncode(Nil *nil, Byte **bytes);
Nil *NilDecode(Byte **bytes, Error *error);
Bool NilEqual(Nil *nil, Nil *other);
Size NilRelease(Nil *nil);

#endif
