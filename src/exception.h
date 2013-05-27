#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "api.h"

Exception *ExceptionCreate(void);

void ExceptionRaise(Exception *exception, Error error);

#endif
