#ifndef CONTEXT_H
#define CONTEXT_H

#include "runtime.h"

void ContextSetValueForIdentifier(Context *context, Value *value, Identifier *id);
Value *ContextGetValueForIdentifier(Context *context, Identifier *id);
Bool ContextEqual(Context *context, Context *other);

#endif
