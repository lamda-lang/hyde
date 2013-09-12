#ifndef BUILTIN_IDENTIFIER_H
#define BUILTIN_IDENTIFIER_H

#include <runtime.h>

Value *IdentifierDecode(Byte **bytes);
Bool IdentifierEqual(Identifier *identifier, Identifier *other);
void IdentifierRelease(Identifier *identifier);

#endif
