#ifndef DO_H
#define DO_H

#include "api.h"

VALUE *DoDecode(Byte **bytes, Error *error);
void DoDealloc(VALUE *doValue);

#endif
