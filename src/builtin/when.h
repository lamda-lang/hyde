#ifndef BUILTIN_WHEN_H
#define BUILTIN_WHEN_H

#include <builtin/api.h>
#include <posix/api.h>
#include <util/api.h>

VALUE *WhenDecode(Byte **bytes, Error *error);

#endif
