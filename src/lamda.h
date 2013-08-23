#ifndef LAMDA_H
#define LAMDA_H

#include "api.h"

void *LamdaDecode(Byte **bytes, VALUE **error);
void LamdaDealloc(VALUE *lamdaVALUE);
Integer64 LamdaHash(VALUE *lamdaVALUE);
Integer8 LamdaArity(VALUE *lamdaVALUE);
void LamdaEnumerate(VALUE *lamdaVALUE, void (*callback)(VALUE *value));
VALUE **LamdaCreateContext(VALUE *lamdaVALUE, VALUE **error);
void LamdaDeallocContext(VALUE **context);
VALUE *LamdaResult(VALUE *lamdaVALUE, VALUE **context, VALUE **error);

#endif
