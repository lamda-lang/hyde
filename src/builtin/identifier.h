#ifndef BUILTIN_IDENTIFIER_H
#define BUILTIN_IDENTIFIER_H

#include <runtime.h>

Value *IdentifierDecode(Byte **bytes);
Bool IdentifierEqual(void *identifierData, void *otherData);
void IdentifierRelease(void *identifierData);

#endif
