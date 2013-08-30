#ifndef LAMDA_H
#define LAMDA_H

#include "runtime.h"

VALUE *LamdaDecode(Byte **bytes, Error *error);
void LamdaDealloc(VALUE *lamdaValue);

#endif
