#ifndef MAP_H
#define MAP_H

#include "runtime.h"

Bool MapDecode(Binary *binary, Integer32 *offset, Value **value);
Bool MapEval(Map *map, Context *context, Stack *stack);
Map *MapSetValueForKey(Map *map, Value *value, Value *key);
Bool MapEqual(Map *map, Map *other);

#endif
