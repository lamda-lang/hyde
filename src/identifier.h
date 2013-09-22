#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "runtime.h"

Identifier *IdentifierDecode(Byte **bytes, Error *error);
Bool IdentifierEqual(Identifier *id, Identifier *other);
Size IdentifierRelease(Identifier *id);

#endif
