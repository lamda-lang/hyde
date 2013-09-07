#ifndef BUILTIN_COMPREHENSION_H
#define BUILTIN_COMPREHENSION_H

#include <builtin/api.h>
#include <posix/api.h>
#include <util/api.h>

VALUE *ComprehensionDecodeList(Byte **bytes, Error *error);
VALUE *ComprehensionDecodeMap(Byte **bytes, Error *error);
VALUE *ComprehensionDecodeSet(Byte **bytes, Error *error);

#endif
