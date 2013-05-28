#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "api.h"

Exception *ExceptionCreate(void);

Status ExceptionStatus(Exception *exception);

Char *ExceptionDescription(Exception *exception);

void ExceptionDealloc(Exception *exception);

void ExceptionRaise(Exception *exception, Error error);

#endif
