#ifndef BUILTIN_IDENTIFIER_H
#define BUILTIN_IDENTIFIER_H

#include <runtime.h>

typedef struct Identifier Identifier;

Identifier *IdentifierDecode(Byte **bytes);
Bool IdentifierEqual(Identifier *id, Identifier *other);
Size IdentifierRelease(Identifier *id);

#endif
