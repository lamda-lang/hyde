#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "runtime.h"

Size IdentifierSize(Identifier *id);
Size IdentifierEncode(Identifier *id, Byte **bytes);
Identifier *IdentifierDecode(Byte **bytes, Error *error);
Value *IdentifierEval(Value *value, Identifier *id, Value *context, Error *error);
Bool IdentifierEqual(Identifier *id, Identifier *other);
Size IdentifierRelease(Identifier *id);

#endif
