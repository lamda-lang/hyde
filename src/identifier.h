#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "runtime.h"

Bool IdentifierDecodePrimitive(Binary *binary, Integer32 *offset, Identifier **id);
Bool IdentifierDecode(Binary *binary, Integer32 *offset, Value **value);
Bool IdentifierEval(Identifier *id, Context *context, Stack *stack);

#endif
