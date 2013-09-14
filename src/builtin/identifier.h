#ifndef BUILTIN_IDENTIFIER_H
#define BUILTIN_IDENTIFIER_H

#include <runtime.h>

typedef struct Identifier Identifier;

Value *IdentifierDecode(Byte **bytes);
Value *IdentifierEval(Identifier *id, Value *context);
Bool IdentifierEqual(Identifier *identifier, Identifier *other);
Size IdentifierRelease(Identifier *identifier);

#endif
