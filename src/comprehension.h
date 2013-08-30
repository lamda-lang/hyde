#ifndef COMPREHENSION_H
#define COMPREHENSION_H

#include "runtime.h"

VALUE *ComprehensionDecodeList(Byte **bytes, Error *error);
VALUE *ComprehensionDecodeMap(Byte **bytes, Error *error);
VALUE *ComprehensionDecodeSet(Byte **bytes, Error *error);

#endif
