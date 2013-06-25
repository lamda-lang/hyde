#ifndef ERROR_H
#define ERROR_H

#include "api.h"

void ErrorSet(Error *error, Error errno);
void ErrorPrint(Error error);

#endif
