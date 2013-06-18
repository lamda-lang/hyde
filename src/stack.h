#ifndef STACK_H
#define STACK_H

#include "api.h"

Status StackPushFrame(Integer32 count, Error *error);

void StackPullFrame(Integer32 count);

Value **StackFrameValues(void);

#endif
