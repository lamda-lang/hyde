#ifndef BUILTIN_RESULT_H
#define BUILTIN_RESULT_H

#include <builtin/api.h>
#include <posix/api.h>
#include <util/api.h>

VALUE *ResultDecode(Byte **bytes, Error *error);

#endif
