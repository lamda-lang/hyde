#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "api.h"

void ExceptionRaise(Exception exception);

Exception ExceptionCatch(void);

#endif
