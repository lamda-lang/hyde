#ifndef GLOBAL_H
#define GLOBAL_H

#include "api.h"

extern Value *GlobalNil;
extern Value *GlobalBooleanTrue;
extern Value *GlobalBooleanFalse;
extern Stack *GlobalStack;

Status GlobalInit(Error *error);
void GlobalDealloc(void);

#endif
