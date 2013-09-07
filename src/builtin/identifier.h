#ifndef BUILTIN_IDENTIFIER_H
#define BUILTIN_IDENTIFIER_H

#include <builtin/api.h>
#include <posix/api.h>
#include <util/api.h>

VALUE *IdentifierDecode(Byte **bytes, Error *error);
void IdentifierDealloc(VALUE *identifierValue);

#endif
