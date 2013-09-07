#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <runtime.h>

VALUE *IdentifierDecode(Byte **bytes, Error *error);
void IdentifierDealloc(VALUE *identifierValue);

#endif
