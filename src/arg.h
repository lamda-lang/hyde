#ifndef ARG_H
#define ARG_H

#include "api.h"

void ArgInit(Char **args, Integer8 count);

Char *ArgRoot(void);

Char *ArgFile(void);

Char **ArgArgs(void);

Integer8 ArgArgsCount(void);

#endif
