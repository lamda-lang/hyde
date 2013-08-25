#ifndef COMPREHENSION_H
#define COMPREHENSION_H

#include "runtime.h"

VALUE *ComprehensionDecodeList(Byte **bytes, VALUE **error);
VALUE *ComprehensionDecodeMap(Byte **bytes, VALUE **error);
VALUE *ComprehensionDecodeSet(Byte **bytes, VALUE **error);

#endif
