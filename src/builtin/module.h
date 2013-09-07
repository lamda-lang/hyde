#ifndef BUILTIN_MODULE_H
#define BUILTIN_MODULE_H

#include <builtin/api.h>
#include <posix/api.h>
#include <util/api.h>

VALUE *ModuleDecode(Byte **bytes, Error *error);

#endif
