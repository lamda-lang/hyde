#ifndef LAMDA_H
#define LAMDA_H

#include "runtime.h"

VALUE *LamdaDecode(Byte **bytes, VALUE **error);
void LamdaDealloc(VALUE *lamdaValue);
Integer64 LamdaHash(VALUE *lamdaValue);

#endif
