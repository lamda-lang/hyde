#ifndef RUNTIME_H
#define RUNTIME_H

#include "api.h"

Status RuntimeMain(Char *path, Char *main, Char **args, Integer8 count, Error *error);

#endif
