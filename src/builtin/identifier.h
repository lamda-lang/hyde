#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <runtime.h>

Value *IdentifierDecode(Byte **bytes, Error *error);
Bool IdentifierEqual(Value *identifierValue, Value *otherValue);
void IdentifierRelease(Value *identifierValue);

#endif
