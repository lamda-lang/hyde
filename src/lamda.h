#ifndef LAMDA_H
#define LAMDA_H

#include "runtime.h"

Bool LamdaDecode(Binary *binary, Integer32 *offset, Value **value);
Bool LamdaEval(Lamda *lamda, Context *context, Stack *stack);
Bool LamdaEqual(Lamda *lamda, Lamda *other);

#endif
